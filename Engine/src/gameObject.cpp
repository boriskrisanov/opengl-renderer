#include "gameObject.hpp"
#include "utils.hpp"
#include <glm/glm.hpp>

using glm::mat4, glm::vec3, glm::radians;

namespace render
{
GameObject::GameObject(Model model, Transform transform) : transform{transform}, model{model}
{
    // Convert render::Vertex vector to float array
    // TODO: Add normal information

    std::vector<float> vertexBufferData;

    for (const Vertex& vertex : this->model.mesh.vertexes)
    {
        vertexBufferData.push_back(vertex.position.x * transform.scale.x);
        vertexBufferData.push_back(vertex.position.y * transform.scale.y);
        vertexBufferData.push_back(vertex.position.z * transform.scale.z);

        vertexBufferData.push_back(vertex.textureCoordinate.x);
        vertexBufferData.push_back(vertex.textureCoordinate.y);
    }

    if (vertexBufferData.empty()) [[unlikely]]
    {
        DEBUG_LOG("warning: GameObject constructor called with empty vertex buffer");
        return;
    }

    DEBUG_LOG("Creating GameObject, vertex buffer length: " << vertexBufferData.size() << ", vertex count: " << model.mesh.vertexCount);

    // Set up OpenGL buffers

    glGenVertexArrays(1, &this->vertexArrayId);
    glBindVertexArray(this->vertexArrayId);

    glGenBuffers(1, &this->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId);

    glBufferData(GL_ARRAY_BUFFER, utils::sizeOfVectorInBytes(vertexBufferData), &vertexBufferData.front(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    // Texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GameObject::draw(render::Shader shader) const
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayId);

    this->model.texture.select();

    mat4 transform{1};
    transform = glm::translate(transform, this->transform.position);
    transform = glm::rotate(transform, radians(this->transform.rotation.x), vec3{1, 0, 0});
    transform = glm::rotate(transform, radians(this->transform.rotation.y), vec3{0, 0, 1});
    transform = glm::rotate(transform, radians(this->transform.rotation.z), vec3{0, 1, 0});

    shader.setUniform("transform", transform);

    glBindVertexArray(this->vertexArrayId);

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) model.mesh.vertexCount);
}
} // namespace render