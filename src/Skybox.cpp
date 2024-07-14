#include "Skybox.hpp"
#include <GL/glew.h>
#include <stb_image.h>

Skybox::Skybox()
{
    // TODO: Allow for user specified texture paths

    glGenTextures(1, &cubemapTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureId);

    int width, height, channels;
    unsigned char *textureData;

    const string textureFileNames[] = {"right", "left", "top", "bottom", "front", "back"};

    for (int i = 0; i < 6; i++)
    {
        const string texturePath = "assets/textures/skybox/" + textureFileNames[i] + ".jpg";
        textureData = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

        if (!textureData) [[unlikely]]
        {
            DEBUG_LOG("Cubemap texture loading failed: " << texturePath);
            return;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

        stbi_image_free(textureData);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Init VBO and VAO
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
}

unsigned int Skybox::getVertexArrayId() const
{
    return vertexArrayId;
}
unsigned int Skybox::getCubemapTextureId() const
{
    return cubemapTextureId;
}
