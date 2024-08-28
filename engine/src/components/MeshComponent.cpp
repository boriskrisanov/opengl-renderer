#include <GL/glew.h>
#include "MeshComponent.hpp"

MeshComponent::MeshComponent(Mesh &mesh, Shader &shader) : mesh{mesh}, shader{shader}
{
    // TODO: Use index buffer
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Convert mesh data to flat array for the vertex buffer
    std::vector<double> bufferData;
    bufferData.reserve(mesh.vertexes.size() * 5);
    for (const Vertex &vertex : mesh.vertexes)
    {
        bufferData.push_back(vertex.position.x);
        bufferData.push_back(vertex.position.y);
        bufferData.push_back(vertex.position.z);

        bufferData.push_back(vertex.textureCoordinate.x);
        bufferData.push_back(vertex.textureCoordinate.y);

        bufferData.push_back(vertex.normal.x);
        bufferData.push_back(vertex.normal.y);
        bufferData.push_back(vertex.normal.z);
    }

    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(double), &bufferData[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_DOUBLE, false, 8 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);

    // Texture coordinate
    glVertexAttribPointer(1, 2, GL_DOUBLE, false, 8 * sizeof(double), (const void*)(3 * sizeof(double)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_DOUBLE, false, 8 * sizeof(double), (const void*)(5 * sizeof(double)));
    glEnableVertexAttribArray(2);
}

unsigned int MeshComponent::getVertexArray() const
{
    return vertexArray;
}
