#pragma once

#include "render/model.hpp"
#include "assets.hpp"
#include <glm/vec3.hpp>
#include "scale.hpp"
#include "shader.hpp"

namespace render
{
class GameObject
{
  public:
    bool isVisible = true;
    GameObject(glm::vec3 position, glm::vec3 rotation, render::assetLoader::ModelName model, render::assetLoader::TextureName texture = assetLoader::TextureName::UV_GRID_256, render::Scale scale = 1);
    const ObjModel *const model;
    const Texture *const texture;
    glm::vec3 position;
    glm::vec3 rotation;
    void render(render::Shader shader) const;

  private:
    const unsigned long long numberOfVertexes;
    unsigned int vertexBuffer;
    unsigned int vertexArray;
};
} // namespace render