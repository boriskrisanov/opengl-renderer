#include "defs.hpp"

int main()
{
    auto window = render::initAndCreateWindow();

    if (!window)
    {
        return 1;
    }

    render::loadShaderFromFile("assets/shaders/vertex.glsl", render::ShaderType::VERTEX);
    render::loadShaderFromFile("assets/shaders/fragment.glsl", render::ShaderType::FRAGMENT);
    auto shaderProgram = render::createShaderProgram();

    render::setVsyncEnabled(true);

    render::initCamera(shaderProgram);
    render::initScene(shaderProgram);

    // render::setWireframeDrawEnabled(true);

    while (!glfwWindowShouldClose(window))
    {
        render::drawFrame(shaderProgram);
    }

    glfwTerminate();
    return 0;
}
