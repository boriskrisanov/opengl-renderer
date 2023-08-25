#include "render/render.hpp"
#include "render/camera.hpp"
#include "render/context.hpp"
#include "render/gameObject.hpp"
#include "render/shader.hpp"
#include "render/skybox.hpp"
#include "ui.hpp"
#include "world.hpp"
#include <memory>
#include <random>


using glm::vec2, std::string;

namespace render
{
RenderContext initAndCreateWindow(glm::vec2 windowSize, std::function<void()> onStart, std::function<void()> onUpdate)
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
        throw std::exception("Failed initialize GLEW");
    }

    DEBUG_LOG("Window init");


    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                              {
        (void) window; // Remove unused parameter warning
        glViewport(0, 0, width, height); });

    DEBUG_LOG("Finished OpenGL init");

    render::Shader shader{"default", {"viewMatrix", "projectionMatrix", "transform"}};

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(window, windowSize, shader, 0.05);
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
        .initScene = onStart,
        .updateScene = onUpdate};
}

void drawFrame(RenderContext context)
{
    context.updateDeltaTime();
    double startTime = glfwGetTime();

    if (!context.isCursorEnabled) [[likely]]
    {
        context.camera->update(context.deltaTime);
    }

    context.skybox->draw();

    context.shader.select();

    context.updateScene();

    for (auto gameObject : context.gameObjects)
    {
        gameObject.render(context.shader);
    }

    double endTime = glfwGetTime();
    const double frameTimeInSeconds = endTime - startTime;

    ui::update(context.window, context.isWireframeDrawEnabled, context.isCursorEnabled, frameTimeInSeconds, [] {});

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
} // namespace render