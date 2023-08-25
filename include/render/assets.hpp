#pragma once

#include "model.hpp"
#include "texture.hpp"

namespace render::assetLoader
{
void loadAssets();
enum class TextureName
{
    CONTAINER,
    GRASS,
    DIRT,
    MISSING_TEXTURE,
    UV_GRID_256
};
enum class ModelName
{
    CUBE,
    SPHERE
};
[[nodiscard]] const render::Texture *getTexture(TextureName name);
[[nodiscard]] const ObjModel *getModel(ModelName name);
} // namespace render::assetLoader