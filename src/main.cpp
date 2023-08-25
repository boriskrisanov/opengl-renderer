#include "game/game.hpp"
#include "render/assets.hpp"
#include "render/context.hpp"
#include "render/render.hpp"
#include "utils.hpp"
#include <iostream>

int main()
{
    try
    {
        render::RenderContext context = render::initAndCreateWindow({1920, 1080}, game::onStart, game::onUpdate);

        render::setVsyncEnabled(true);

        render::assetLoader::loadAssets();

        glClearColor(1, 1, 1, 1);

        context.gameObjects.push_back({{8, 5, 8}, {0, 0, 0}, render::assetLoader::ModelName::CUBE, render::assetLoader::TextureName::UV_GRID_256});

        render::runMainLoop(context);

        glfwTerminate();
        return 0;
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
