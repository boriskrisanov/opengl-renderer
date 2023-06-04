#include "defs.hpp"
#include <GLFW/glfw3.h>

using glm::vec2, std::string;

namespace render
{
GLFWwindow *window;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera{};
const float WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
std::vector<std::shared_ptr<Cube>> cubes;
bool isCursorEnabled = false;
bool isWireframeDrawEnabled = false;
double frameTimeInMilliseconds = 0;
string openGlVersion;
string rendererInfo;

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

    return window;
}

void initCamera(unsigned int shaderProgram)
{
    camera = Camera{window, vec2(WINDOW_WIDTH, WINDOW_HEIGHT), shaderProgram, 0.05f};
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
    if (input::isKeyDown(window, input::ESCAPE))
    {
        isCursorEnabled = !isCursorEnabled;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: Add delay between updates
    // TODO: FPS counter
    auto cameraPosition = camera.position;
    ImGui::Text("%s", std::format("Camera position: {}, {}, {} ", cameraPosition.x, cameraPosition.y, cameraPosition.z).c_str());
    ImGui::Text("%s", std::format("Frame time: {}ms", frameTimeInMilliseconds).c_str());
    ImGui::Text("%s", std::format("OpenGL version: {}", openGlVersion).c_str());
    ImGui::Text("%s", std::format("Renderer: {}", rendererInfo).c_str());

    if (ImGui::Button("Toggle wireframe"))
    {
        setWireframeDrawEnabled(!isWireframeDrawEnabled);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void initScene(unsigned int shaderId)
{
    Texture texture{"assets/textures/container.jpg"};

    cubes.push_back(std::shared_ptr<Cube>(new Cube{{0, 0, 0}, {0, 0, 0}, shaderId, texture}));
    cubes.push_back(std::shared_ptr<Cube>(new Cube{{2, 0, 0}, {0, 0, 0}, shaderId, texture}));

    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cubes.push_back(std::shared_ptr<Cube>(new Cube{{i + 3, k, j + 3}, {0, 0, 0}, shaderId, texture}));
            }
        }
    }
}

void drawFrame()
{
    updateDeltaTime();
    double startTime = glfwGetTime();

    glfwSetInputMode(window, GLFW_CURSOR, isCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    camera.update();

    for (std::shared_ptr<Cube> cube : cubes)
    {
        cube->render();
    }

    cubes.at(0)->rotation.z = glfwGetTime() * 20;
    cubes.at(1)->position.y = sin(glfwGetTime());

    updateUI();

    double endTime = glfwGetTime();

    frameTimeInMilliseconds = (endTime - startTime) * 1000;

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
} // namespace render