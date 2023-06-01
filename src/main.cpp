#include "defs.hpp"

int main()
{
    auto window = render::initAndCreateWindow();

    render::loadShaderFromFile("assets/shaders/vertex.glsl", render::ShaderType::VERTEX);
    render::loadShaderFromFile("assets/shaders/fragment.glsl", render::ShaderType::FRAGMENT);
    auto shaderProgram = render::createShaderProgram();

    render::setVsyncEnabled(true);

    render::initCamera(shaderProgram);

    // render::setWireframeDrawEnabled(true);

    while (!glfwWindowShouldClose(window))
    {
        render::drawFrame();
    }

    glfwTerminate();
    return 0;
}
