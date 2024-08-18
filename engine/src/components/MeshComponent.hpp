#pragma once

#include "../Component.hpp"
#include "../Mesh.hpp"
#include "../Shader.hpp"

struct MeshComponent : public Component
{
    const Mesh &mesh;
    const Shader &shader;
    MeshComponent(Mesh &mesh, Shader &shader);
    [[nodiscard]] unsigned int getVertexArray() const;

  private:
    unsigned int vertexBuffer = 0;
    unsigned int vertexArray = 0;
};