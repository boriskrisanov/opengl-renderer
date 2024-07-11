#include <GL/glew.h>
#include "Renderer.hpp"
#include <exception>
#include "utils.hpp"

Renderer::Renderer(Vector2<int> windowSize) : windowSize{windowSize}
{
    if (!glfwInit())
    {
        throw std::exception{"Failed to initialise GLFW"};
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::exception{"Failed to create window"};
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        throw std::exception{"Failed to initialise GLEW"};
    }

    glEnable(GL_DEPTH_TEST);

    DEBUG_LOG("OpenGL version: " << glGetString(GL_VERSION));
    DEBUG_LOG("OpenGL renderer: " << glGetString(GL_RENDERER));
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
