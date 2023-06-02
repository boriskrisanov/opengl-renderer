#include "defs.hpp"
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>

using namespace render;
using glm::mat4, glm::vec3, glm::radians;

// Rotation is in degrees
Cube::Cube(vec3 position, vec3 rotation, unsigned int shaderId) : shaderId(shaderId), position{position}, rotation{rotation}
{
    DEBUG_LOG("Cube init");

    unsigned int vertexBuffer;

    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->triangleVertices), this->triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int indexBuffer;

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
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

    glDrawElements(GL_TRIANGLES, sizeof(this->indexes) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}