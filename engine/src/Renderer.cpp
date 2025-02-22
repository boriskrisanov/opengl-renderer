#include <GL/glew.h>

#include "Renderer.hpp"
#include "utils.hpp"
#include <stdexcept>

using std::vector, std::string;

Renderer::Renderer(Vector2<int> windowSize)
    : windowSize{windowSize}
{
    if (!glfwInit())
    {
        throw std::runtime_error{"Failed to initialise GLFW"};
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error{"Failed to create window"};
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error{"Failed to initialise GLEW"};
    }

    glEnable(GL_DEPTH_TEST);

    DEBUG_LOG("OpenGL version: " + string{reinterpret_cast<const char*>(glGetString(GL_VERSION))});
    DEBUG_LOG("OpenGL renderer: " + string{reinterpret_cast<const char*>(glGetString(GL_RENDERER))});

    shader = make_unique<Shader>("default", vector<string>{"viewMatrix", "projectionMatrix", "modelMatrix", "lightPosition", "cameraPosition", "worldSpacePosition"});
    shader->select();
}

Renderer::~Renderer()
{
    glfwTerminate();
}

bool Renderer::isWindowClosed() const
{
    return glfwWindowShouldClose(window);
}

Vector2<int> Renderer::getWindowSize() const
{
    return windowSize;
}
