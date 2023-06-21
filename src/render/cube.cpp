#include "defs.hpp"

using namespace render;
using glm::mat4, glm::vec3, glm::radians;

// Rotation is in degrees
Cube::Cube(vec3 position, vec3 rotation, const Texture* const texture) : texture(texture), position{position}, rotation{rotation}
{
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
    this->texture->select();
}

void Cube::render(render::Shader shader) const
{
    // TODO: Improve efficiency. A lot of this can be done in the constructor and not on every frame.
    mat4 transform{1};
    transform = glm::translate(transform, this->position);
    transform = glm::rotate(transform, radians(this->rotation.x), vec3{1, 0, 0});
    transform = glm::rotate(transform, radians(this->rotation.y), vec3{0, 0, 1});
    transform = glm::rotate(transform, radians(this->rotation.z), vec3{0, 1, 0});
    transform = glm::scale(transform, {0.5, 0.5, 0.5}); // TODO: Add scale parameter

    auto transformUniformLocation = glGetUniformLocation(shader.id, "transform");
    glUniformMatrix4fv(transformUniformLocation, 1, false, glm::value_ptr(transform));

    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // this->texture.select();

    // glUseProgram(shaderId);
    glBindVertexArray(this->vertexArray);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(this->vertexes) / sizeof(float) * 5);
}