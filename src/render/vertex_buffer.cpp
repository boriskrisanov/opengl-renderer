#include "defs.hpp"

namespace render
{
VertexBuffer::VertexBuffer(std::vector<Vertex> data)
{
    glGenBuffers(1, &this->id);
    this->select();

    std::vector<float> glVertexData;

    for (Vertex vertex : data)
    {
        // Attribute 0
        glVertexData.push_back(vertex.positionX);
        glVertexData.push_back(vertex.positionY);
        glVertexData.push_back(vertex.positionZ);

        // Attribute 1
        glVertexData.push_back(vertex.textureCoordinateX);
        glVertexData.push_back(vertex.textureCoordinateY);
    }

    glBufferData(GL_ARRAY_BUFFER, glVertexData.size() * sizeof(float), &glVertexData[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);
}

VertexBuffer::~VertexBuffer()
{
    // TODO
}

void VertexBuffer::select()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}
} // namespace render