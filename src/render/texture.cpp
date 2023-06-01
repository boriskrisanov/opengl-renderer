#include "defs.hpp"

render::Texture::Texture(std::string sourcePath)
{
    this->textureData = stbi_load(sourcePath.c_str(), &width, &height, nullptr, 0);

    if (!textureData)
    {
        DEBUG_LOG("Failed to load texture");
        // TODO: Add proper error handling
    }
}

render::Texture::~Texture()
{
    DEBUG_LOG("Texture destroyed");
    stbi_image_free((void *)textureData);
}