#include "defs.hpp"

using namespace render;
using glm::mat4, glm::vec3, glm::radians;

// Rotation is in degrees
Cube::Cube(vec3 position, vec3 rotation, unsigned int shaderId) : shaderId(shaderId), position{position}, rotation{rotation}
{
    DEBUG_LOG("Cube init");

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);

    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertexes), this->vertexes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    // Load texture
    int width, height, channels;
    unsigned char *textureData = stbi_load("assets/textures/container.jpg", &width, &height, &channels, 0);

    if (!textureData)
    {
        DEBUG_LOG("Texture loading failed");
        return;
    }

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
}

void Cube::render() const
{
    // TODO: Improve efficiency. A lot of this can be done in the constructor and not on every frame.
    mat4 transform{1};
    transform = glm::translate(transform, this->position);
    transform = glm::rotate(transform, radians(this->rotation.x), vec3{1, 0, 0});
    transform = glm::rotate(transform, radians(this->rotation.y), vec3{0, 0, 1});
    transform = glm::rotate(transform, radians(this->rotation.z), vec3{0, 1, 0});

    unsigned int transformLocation = glGetUniformLocation(this->shaderId, "transform");
    glUniformMatrix4fv(transformLocation, 1, false, glm::value_ptr(transform));

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glUseProgram(this->shaderId);
    glBindVertexArray(this->vertexArray);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(this->vertexes) / sizeof(float) * 5);
}