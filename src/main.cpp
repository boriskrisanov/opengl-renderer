#include "defs.hpp"

int main()
{
    auto window = render::initAndCreateWindow();

    if (!window)
    {
        return 1;
    }

    render::Shader shader{"default", {"viewMatrix", "projectionMatrix", "transform"}};

    render::setVsyncEnabled(true);
    
    render::assetLoader::loadAssets();

    render::initCamera(shader);
    render::initScene();

    // glClearColor(30.0 / 100.0, 193.0 / 100.0, 234.0 / 100.0, 1);
    glClearColor(1, 1, 1, 1);

    // render::setWireframeDrawEnabled(true);

    while (!glfwWindowShouldClose(window))
    {
        render::drawFrame(shader);
    }

    glfwTerminate();
    return 0;
}
