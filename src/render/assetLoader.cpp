#include "render/texture.hpp"
#include "render/model.hpp"
#include "render/assets.hpp"

#define EXIT_IF_ASSETS_NOT_LOADED()                                      \
    if (!assetsLoaded) [[unlikely]]                                      \
    {                                                                    \
        DEBUG_LOG(__func__ << "() called before loadAssets(), exiting"); \
        exit(1);                                                         \
    }

namespace render::assetLoader
{

// No need to free pointers because they're used until the end of the program

render::Texture *container = nullptr;
render::Texture *grass = nullptr;
render::Texture *dirt = nullptr;
render::Texture *uvGrid256 = nullptr;

render::ObjModel *cube = nullptr;
render::ObjModel *sphere = nullptr;

bool assetsLoaded = false;

void loadAssets()
{
    if (assetsLoaded) [[unlikely]]
    {
        DEBUG_LOG("warning: loadAssets() called more than once");
        return;
    }

    DEBUG_LOG("Started asset loading");

    container = new render::Texture{"assets/textures/container.jpg"};
    grass = new render::Texture{"assets/textures/grass.jpg"};
    dirt = new render::Texture{"assets/textures/dirt.jpg"};
    uvGrid256 = new render::Texture{"assets/textures/uv_grid_256.jpg"};

    cube = new render::ObjModel{"assets/cube.obj"};
    sphere = new render::ObjModel{"assets/sphere.obj"};

    assetsLoaded = true;

    DEBUG_LOG("Finished asset loading");
}

const Texture *getTexture(TextureName name)
{
    EXIT_IF_ASSETS_NOT_LOADED();

    using enum TextureName;

    switch (name)
    {
    case CONTAINER:
        return container;
    case GRASS:
        return grass;
    case DIRT:
        return dirt;
    case MISSING_TEXTURE:
    case UV_GRID_256:
        return uvGrid256;
    }
}

const render::ObjModel *getModel(ModelName name)
{
    EXIT_IF_ASSETS_NOT_LOADED();

    using enum ModelName;

    switch (name)
    {
    case CUBE:
        return cube;
    case SPHERE:
        return sphere;
    }
}
} // namespace render::assetLoader