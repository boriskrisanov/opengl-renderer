#include "defs.hpp"

using namespace render;

Cube::Cube()
{
    DEBUG_LOG("Cube init");

    unsigned int vertexBuffer = 0;

    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->triangleVertices), this->triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int indexBuffer = 0;

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
}

void Cube::render() const
{
    // glDrawElements(GL_TRIANGLES, 36 / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
    glDrawElements(GL_TRIANGLES, sizeof(this->indexes) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}