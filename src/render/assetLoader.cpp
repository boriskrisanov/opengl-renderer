#include "defs.hpp"

namespace render::assetLoader
{

// No need to free pointers because they're used until the end of the program

render::Texture *container = nullptr;

render::ObjModel *cube = nullptr;
render::ObjModel *sphere = nullptr;

bool assetsLoaded = false;

void loadAssets()
{
    DEBUG_LOG("Started asset loading");

    container = new render::Texture{"assets/textures/container.jpg"};

    cube = new render::ObjModel{"assets/cube.obj"};
    sphere = new render::ObjModel{"assets/sphere.obj"};

    assetsLoaded = true;

    DEBUG_LOG("Finished asset loading");
}

const Texture *getTexture(TextureName name)
{
    if (!assetsLoaded) [[unlikely]]
    {
        DEBUG_LOG("getTexture() called before loadAssets(), exiting");
        exit(1);
    }

    switch (name)
    {
    case TextureName::CONTAINER:
        return container;
    }
}

const render::ObjModel *getModel(ModelName name)
{
    if (!assetsLoaded) [[unlikely]]
    {
        DEBUG_LOG("getModel() called before loadAssets(), exiting");
        exit(1);
    }

    switch (name)
    {
    case ModelName::CUBE:
        return cube;
    case ModelName::SPHERE:
        return sphere;
    }
}
} // namespace render::assetLoader