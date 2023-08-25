#include "render/render.hpp"
#include "render/gameObject.hpp"
#include "ui.hpp"
#include "world.hpp"
#include <random>
#include "render/camera.hpp"
#include "render/skybox.hpp"

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
std::vector<world::Chunk> chunks;
std::shared_ptr<Skybox> skybox;
static std::random_device randomDevice;
static std::mt19937 rng{randomDevice()};
static std::uniform_int_distribution<int> uniformIntDistribution{0, INT_MAX};
std::vector<GameObject> gameObjects;
const double SECONDS_BETWEEN_COUNTER_UPDATES = 0.25;
const double SECONDS_BETWEEN_CURSOR_STATE_UPDATES = 0.5;
double secondsUntilNextCounterUpdate = SECONDS_BETWEEN_COUNTER_UPDATES;
double secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;

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

    ui::init(window);

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                              {
        (void) window; // Remove unused parameter warning
        glViewport(0, 0, width, height); });

    DEBUG_LOG("Finished OpenGL init");

    return window;
}

void initCamera(render::Shader shader)
{
    camera = std::make_shared<Camera>(Camera{window, vec2(WINDOW_WIDTH, WINDOW_HEIGHT), shader, 5});
}

void updateDeltaTime()
{
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void initScene()
{
    chunks = world::generateTerrain(uniformIntDistribution(rng), {4, 4});
    skybox = std::make_shared<Skybox>(Skybox{camera});

    gameObjects.push_back(GameObject{{5, 5, 5}, {0, 0, 0}, render::assetLoader::ModelName::SPHERE, render::assetLoader::TextureName::CONTAINER});
    gameObjects.push_back(GameObject{{8, 5, 8}, {0, 0, 0}, render::assetLoader::ModelName::CUBE, render::assetLoader::TextureName::UV_GRID_256});
}

void drawFrame(render::Shader shader)
{
    updateDeltaTime();
    double startTime = glfwGetTime();

    // TODO: Don't call this every frame
    glfwSetInputMode(window, GLFW_CURSOR, isCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    if (!isCursorEnabled) [[likely]]
    {
        camera->update(deltaTime);
    }

    skybox->draw();

    shader.select();

    for (auto chunk : chunks)
    {
        chunk.draw(shader);
    }

    for (auto gameObject : gameObjects)
    {
        gameObject.render(shader);
    }

    // TODO: Move parameters to ui::init()
    ui::update(window, isCursorEnabled, secondsUntilNextCursorStateUpdate, SECONDS_BETWEEN_CURSOR_STATE_UPDATES, frameTimeInMilliseconds, camera,
               []
               {
                   chunks.clear();
                   chunks = world::generateTerrain(uniformIntDistribution(rng), {4, 4});
               });

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
} // namespace render