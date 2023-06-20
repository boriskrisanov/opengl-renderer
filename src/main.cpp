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

    render::textureLoader::loadTextures();

    render::initCamera(shaderProgram);
    render::initScene();

    // glClearColor(30.0 / 100.0, 193.0 / 100.0, 234.0 / 100.0, 1);
    glClearColor(1, 1, 1, 1);

    // render::setWireframeDrawEnabled(true);

    while (!glfwWindowShouldClose(window))
    {
        render::drawFrame(shaderProgram);
    }

    glfwTerminate();
    return 0;
}
