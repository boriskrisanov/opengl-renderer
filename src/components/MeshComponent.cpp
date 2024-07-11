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
    vector<double> bufferData;
    bufferData.reserve(mesh.vertexes.size() * 3);
    for (const Vertex &vertex : mesh.vertexes)
    {
        bufferData.push_back(vertex.position.x);
        bufferData.push_back(vertex.position.y);
        bufferData.push_back(vertex.position.z);
    }

    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(double), &bufferData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, false, 3 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);
}

unsigned int MeshComponent::getVertexArray() const
{
    return vertexArray;
}
