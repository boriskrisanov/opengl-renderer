#include "render/render.hpp"
#include "render/camera.hpp"
#include "render/context.hpp"
#include "render/gameObject.hpp"
#include "render/shader.hpp"
#include "render/skybox.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include <algorithm>
#include <memory>
#include <random>
#include <type_traits>

using glm::vec2, std::string;

namespace render
{
std::vector<std::shared_ptr<GameObject>> gameObjectAdditionQueue;

RenderContext initAndCreateWindow(glm::vec2 windowSize, std::function<void()> onStart, std::function<void(float deltaTime)> onUpdate)
{
    if (!glfwInit())
    {
        throw std::exception("Failed to initialize GLFW");
    }

    GLFWwindow *window = glfwCreateWindow(windowSize.x, windowSize.y, "Game", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        throw std::exception("Failed to create window");
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        throw std::exception("Failed to initialize GLEW");
    }

    DEBUG_LOG("Window init");

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                              {
        (void) window; // Remove unused parameter warning
        glViewport(0, 0, width, height); });

    DEBUG_LOG("Finished OpenGL init");

    render::assetLoader::loadAssets();

    render::Shader shader{"default", {"viewMatrix", "projectionMatrix", "transform"}};

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(window, windowSize, shader, 10);
    const std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(camera);

    ui::init(window, camera);

    onStart();

    return RenderContext{
        .window = window,
        .deltaTime = 0,
        .lastFrame = 0,
        .windowSize = windowSize,
        .isWireframeDrawEnabled = false,
        .isCursorEnabled = false,
        .frameTimeInMilliseconds = 0,
        .skybox = skybox,
        .gameObjects = {},
        .shader = shader,
        .camera = camera,
        .onStart = onStart,
        .onUpdate = onUpdate};
}

void drawFrame(RenderContext &context)
{
    context.updateDeltaTime();
    const double startTime = glfwGetTime();

    utils::pushBackVectorToVector(context.gameObjects, gameObjectAdditionQueue);
    gameObjectAdditionQueue.clear();

    if (!context.isCursorEnabled) [[likely]]
    {
        context.camera->update(context.deltaTime);
    }

    context.skybox->draw();

    context.shader.select();

    context.onUpdate(context.deltaTime);

    for (auto gameObject : context.gameObjects)
    {
        gameObject->draw(context.shader);
    }

    const double endTime = glfwGetTime();
    const double frameTimeInSeconds = endTime - startTime;

    ui::update(context.window, context.isWireframeDrawEnabled, context.isCursorEnabled, frameTimeInSeconds);

    glfwSwapBuffers(context.window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void setWireframeDrawEnabled(bool isEnabled)
{
    glPolygonMode(GL_FRONT_AND_BACK, isEnabled ? GL_LINE : GL_FILL);
}

void setVsyncEnabled(bool enabled)
{
    glfwSwapInterval((int)enabled);
}

void runMainLoop(RenderContext context)
{
    while (!glfwWindowShouldClose(context.window))
    {
        render::drawFrame(context);
    }
}

void _addGameObject(std::shared_ptr<GameObject> gameObject)
{
    gameObjectAdditionQueue.push_back(gameObject);
}
} // namespace render