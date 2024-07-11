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
    bufferData.reserve(mesh.vertexes.size() * 5);
    for (const Vertex &vertex : mesh.vertexes)
    {
        bufferData.push_back(vertex.position.x);
        bufferData.push_back(vertex.position.y);
        bufferData.push_back(vertex.position.z);

        bufferData.push_back(vertex.textureCoordinate.x);
        bufferData.push_back(vertex.textureCoordinate.y);
    }

    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(double), &bufferData[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_DOUBLE, false, 5 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_DOUBLE, false, 5 * sizeof(double), (const void*)(3 * sizeof(double)));
    glEnableVertexAttribArray(1);
}

unsigned int MeshComponent::getVertexArray() const
{
    return vertexArray;
}
