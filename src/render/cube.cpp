#include "defs.hpp"

using namespace render;
using glm::mat4, glm::vec3, glm::radians;

// Rotation is in degrees
Cube::Cube(vec3 position, vec3 rotation, unsigned int shaderId) : shaderId(shaderId), position{position}, rotation{rotation}
{
    DEBUG_LOG("Cube init");

    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->triangleVertices), this->triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
}

void Cube::render() const
{
    mat4 transform{1};
    transform = glm::translate(transform, this->position);
    transform = glm::rotate(transform, radians(this->rotation.x), vec3{1, 0, 0});
    transform = glm::rotate(transform, radians(this->rotation.y), vec3{0, 0, 1});
    transform = glm::rotate(transform, radians(this->rotation.z), vec3{0, 1, 0});

    unsigned int transformLocation = glGetUniformLocation(this->shaderId, "transform");
    glUniformMatrix4fv(transformLocation, 1, false, glm::value_ptr(transform));

    glBindBuffer(GL_INDEX_ARRAY, indexBuffer);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glDrawElements(GL_TRIANGLES, sizeof(this->indexes) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}