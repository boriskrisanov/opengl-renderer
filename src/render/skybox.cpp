#include "defs.hpp"

using std::string;

namespace render
{
Skybox::Skybox(const std::shared_ptr<const Camera> camera) : shader{"skybox", {"viewMatrix", "projectionMatrix"}}, camera{camera}
{
    glGenTextures(1, &this->cubemapTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTextureId);

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
    glGenVertexArrays(1, &this->vertexArrayId);
    glBindVertexArray(this->vertexArrayId);

    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexes), this->vertexes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
}

void Skybox::draw() const
{
    glDepthMask(false);

    this->shader.select();

    const glm::mat4 viewMatrixWithoutTranslation = glm::mat3(this->camera->viewMatrix);

    this->shader.setUniform("viewMatrix", viewMatrixWithoutTranslation);
    this->shader.setUniform("projectionMatrix", this->camera->projectionMatrix);

    glBindVertexArray(this->vertexArrayId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTextureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(true);
}

} // namespace render