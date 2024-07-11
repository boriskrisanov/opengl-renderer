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
