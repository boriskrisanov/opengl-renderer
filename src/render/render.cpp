#include "defs.hpp"

using glm::vec2, std::string;

namespace render
{
GLFWwindow *window;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
std::shared_ptr<Camera> camera;
const float WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
bool isCursorEnabled = false;
bool isWireframeDrawEnabled = false;
double frameTimeInMilliseconds = 0;
string openGlVersion;
string rendererInfo;
std::vector<world::Chunk> chunks;
const double SECONDS_BETWEEN_COUNTER_UPDATES = 0.25;
const double SECONDS_BETWEEN_CURSOR_STATE_UPDATES = 0.5;
double secondsUntilNextCounterUpdate = SECONDS_BETWEEN_COUNTER_UPDATES;
double secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;
std::shared_ptr<Skybox> skybox;
static std::random_device randomDevice;
static std::mt19937 rng{randomDevice()};
static std::uniform_int_distribution<int> uniformIntDistribution{0, INT_MAX};

GLFWwindow *initAndCreateWindow()
{
    if (!glfwInit())
    {
        return nullptr;
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        DEBUG_LOG("Failed to create window");
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        DEBUG_LOG("Failed initialize GLEW");
        return nullptr;
    }

    DEBUG_LOG("Window init");

    openGlVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    rendererInfo = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    // imgui setup

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_DEPTH_TEST);

    DEBUG_LOG("Finished OpenGL init");

    return window;
}

void initCamera(render::Shader shader)
{
    camera = std::make_shared<Camera>(Camera{window, vec2(WINDOW_WIDTH, WINDOW_HEIGHT), shader, 0.05f});
}

void updateDeltaTime()
{
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void updateUI()
{
    // TODO: Increase font size
    if (input::isKeyDown(window, input::ESCAPE) && secondsUntilNextCursorStateUpdate <= 0)
    {
        isCursorEnabled = !isCursorEnabled;
        secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: FPS counter
    auto cameraPosition = camera->position;
    ImGui::Text("%s", std::format("Camera position: {}, {}, {} ", cameraPosition.x, cameraPosition.y, cameraPosition.z).c_str());
    ImGui::Text("%s", std::format("Frame time: {}ms", frameTimeInMilliseconds).c_str());
    ImGui::Text("%s", std::format("OpenGL version: {}", openGlVersion).c_str());
    ImGui::Text("%s", std::format("Renderer: {}", rendererInfo).c_str());

    if (ImGui::Button("Toggle wireframe"))
    {
        setWireframeDrawEnabled(!isWireframeDrawEnabled);
    }

    ImGui::Begin("Terrain");

    if (ImGui::Button("Regenerate terrain"))
    {
        chunks.clear();
        chunks = world::generateTerrain(uniformIntDistribution(rng), {4, 4});
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void initScene()
{
    chunks = world::generateTerrain(uniformIntDistribution(rng), {4, 4});
    skybox = std::make_shared<Skybox>(Skybox{camera});
}

void drawFrame(render::Shader shader)
{
    updateDeltaTime();
    double startTime = glfwGetTime();

    glfwSetInputMode(window, GLFW_CURSOR, isCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    if (!isCursorEnabled) [[likely]]
    {
        camera->update();
    }

    skybox->draw();

    shader.select();
    for (auto chunk : chunks)
    {
        render::drawChunk(chunk, shader);
    }

    updateUI();

    double endTime = glfwGetTime();
    const double frameTimeInSeconds = endTime - startTime;
    secondsUntilNextCounterUpdate -= frameTimeInSeconds;
    secondsUntilNextCursorStateUpdate -= frameTimeInSeconds;

    if (secondsUntilNextCounterUpdate <= 0)
    {
        frameTimeInMilliseconds = frameTimeInSeconds * 1000;
        secondsUntilNextCounterUpdate = SECONDS_BETWEEN_COUNTER_UPDATES;
    }

    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void setWireframeDrawEnabled(bool isEnabled)
{
    isWireframeDrawEnabled = isEnabled;
    glPolygonMode(GL_FRONT_AND_BACK, isEnabled ? GL_LINE : GL_FILL);
}

void setVsyncEnabled(bool enabled)
{
    glfwSwapInterval((int)enabled);
}

void drawChunk(world::Chunk chunk, render::Shader shader)
{
    for (auto block : chunk.blocks)
    {
        block->render(shader);
    }
}
} // namespace render