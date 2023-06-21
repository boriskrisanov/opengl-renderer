#include "defs.hpp"


namespace render::textureLoader
{

// No need to free pointers because they're used until the end of the program

render::Texture *container = nullptr;

void loadTextures()
{
    container = new render::Texture{"assets/textures/container.jpg"};
}

const Texture *getTexture(TextureName name)
{
    switch (name)
    {
    case TextureName::CONTAINER:
        return container;
    }
}
} // namespace render::textureLoader