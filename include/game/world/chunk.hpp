#pragma once

#include <glm/glm.hpp>
#include <array>
#include "block/block.hpp"
#include "render/shader.hpp"
#include "render/gameObject.hpp"

namespace world
{
class Chunk : public render::GameObject
{
  public:
    Chunk(glm::vec2 position, std::array<std::array<std::array<Block *, 16>, 16>, 16>);
    void draw(render::Shader shader);
    void updateBlockVisibility();
    glm::vec2 position;
    std::array<std::array<std::array<Block *, 16>, 16>, 16> blocks;
    unsigned int vertexArray;
};
}