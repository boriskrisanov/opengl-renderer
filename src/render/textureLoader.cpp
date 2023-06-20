#include "defs.hpp"


namespace render::textureLoader
{

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