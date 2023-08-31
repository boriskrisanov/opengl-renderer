#include "render.hpp"
#include "camera.hpp"
#include "gameObject.hpp"
#include "shader.hpp"
#include "skybox.hpp"
#include "utils.hpp"
#include <algorithm>
#include <memory>
#include <type_traits>
#include "ui.hpp"

using glm::vec2, std::string;

namespace render
{
Renderer::Renderer(WindowSize windowSize, std::function<void()> onStart, std::function<void(float deltaTime)> onUpdate)
{   
    DEBUG_LOG("Creating new renderer");

    const bool glfwInitSuccessful = glfwInit();

    if (!glfwInitSuccessful) [[unlikely]]
    {
        throw std::exception("Failed to initialize GLFW");
    }

    window = glfwCreateWindow(windowSize.width, windowSize.height, "Game", nullptr, nullptr);

    if (window == nullptr) [[unlikely]]
    {
        glfwTerminate();
        throw std::exception("Failed to create window");
    }

    glfwMakeContextCurrent(window);

    const GLenum glewInitStatus = glewInit();

    if (glewInitStatus != GLEW_OK) [[unlikely]]
    {
        throw std::exception("Failed to initialize GLEW");
        glfwTerminate();
    }

    DEBUG_LOG("Window init completed");

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            (void)window; // Remove unused parameter warning
            glViewport(0, 0, width, height); 
        }
    );

    DEBUG_LOG("Finished OpenGL init");

    glClearColor(1, 1, 1, 1);

    shader = std::make_shared<Shader>("default", std::vector<string>{ "viewMatrix", "projectionMatrix", "transform" });

    // TODO: implement better asset management
    // render::assetLoader::loadAssets();

    camera = std::make_shared<Camera>(window, windowSize, *shader, 10.0f);

    // TODO: Initialize skybox in scene
    const std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>(*camera.get());

    currentScene = std::make_shared<Scene>(*skybox.get());

    ui::init(window, camera);

    onStart();
}

Renderer::~Renderer()
{
    // TODO: Free OpenGL resources
}

void Renderer::begin()
{
    // TODO: Use separate thread for rendering
    while (!this->shouldExit && !glfwWindowShouldClose(window)) [[likely]]
    {
        this->drawFrame();
    }
}

void Renderer::exit() noexcept
{
    this->shouldExit = true;
}

void Renderer::loadScene(std::shared_ptr<Scene> scene) noexcept
{
    currentScene = scene;
}

double Renderer::getFrameTime() const noexcept
{
    return this->currentFrameTime;
}

double Renderer::getDeltaTime() const noexcept
{
    return this->deltaTime;
}

void Renderer::drawFrame()
{
    updateDeltaTime();

    const double startTime = glfwGetTime();

    if (isCursorEnabled)
    {
        camera->update((float) deltaTime);
    }

    currentScene->draw(shader);


    const double endTime = glfwGetTime();
    const double frameTimeInSeconds = endTime - startTime;

    ui::update(window, wireframeDrawEnabled, isCursorEnabled, frameTimeInSeconds);

    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

void Renderer::updateDeltaTime() noexcept
{
    const double currentTime = glfwGetTime();
    deltaTime = currentTime - this->lastTime;
    lastTime = currentTime;
}
} // namespace render