#include "defs.hpp"

using glm::mat4, glm::vec3, glm::radians;

namespace render
{

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, std::shared_ptr<ObjModel> model, std::shared_ptr<Texture> texture)
    : model{model}, texture{texture}, position{position}, rotation{rotation}, numberOfVertexes{model->vertexes.size()}
{
    // Convert render::Vertex vector to float array
    // TODO: Add normal information

    std::vector<float> vertexBufferData;

    for (Vertex vertex : model->vertexes)
    {
        vertexBufferData.push_back(vertex.position.x);
        vertexBufferData.push_back(vertex.position.y);
        vertexBufferData.push_back(vertex.position.z);

        vertexBufferData.push_back(vertex.textureCoordinate.x);
        vertexBufferData.push_back(vertex.textureCoordinate.y);
    }

    // Set up OpenGL buffers

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);

    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, utils::sizeOfVectorInBytes(vertexBufferData), &vertexBufferData.front(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);

    // Texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, utils::sizeOfVectorInBytes(vertexBufferData), &vertexBufferData.front(), GL_STATIC_DRAW);
    this->texture->select();
}

void GameObject::render(render::Shader shader) const
{
    mat4 transform{1};
    transform = glm::translate(transform, this->position);
    transform = glm::rotate(transform, radians(this->rotation.x), vec3{1, 0, 0});
    transform = glm::rotate(transform, radians(this->rotation.y), vec3{0, 0, 1});
    transform = glm::rotate(transform, radians(this->rotation.z), vec3{0, 1, 0});
    // transform = glm::scale(transform, {0.5, 0.5, 0.5}); // TODO: Add scale parameter

    auto transformUniformLocation = glGetUniformLocation(shader.id, "transform");
    glUniformMatrix4fv(transformUniformLocation, 1, false, glm::value_ptr(transform));

    glBindVertexArray(this->vertexArray);

    glDrawArrays(GL_TRIANGLES, 0, numberOfVertexes);
}
} // namespace render