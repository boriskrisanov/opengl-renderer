#include "render.hpp"
#include "texture.hpp"
#include <stb_image.h>

using std::string;

namespace render
{

Texture::Texture(string path)
{
    DEBUG_LOG("Loading texture " << path);

    int width, height, channels;
    unsigned char *textureData = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!textureData) [[unlikely]]
    {
        DEBUG_LOG("Texture loading failed");
        return;
    }

    glGenTextures(1, &this->id);
    this->select();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
}

void Texture::select() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}
} // namespace render
