#pragma once

#include "glm/glm.hpp"
#include "render.hpp"
#include <algorithm>
#include <array>

namespace world
{
class Block
{
  public:
  // clang-format off
    const std::array<float, 5 * 6> positiveXFaceVertexes = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
    };
    const std::array<float, 5 * 6> negativeXFaceVertexes = {
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f

    };
    const std::array<float, 5 * 6> positiveYFaceVertexes = {
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f

    };
    const std::array<float, 5 * 6> negativeYFaceVertexes = {
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f

    };
    const std::array<float, 5 * 6> positiveZFaceVertexes = {
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f

    };
    const std::array<float, 5 * 6> negativeZFaceVertexes = {
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // clang-format on

    glm::vec3 position;
    bool positiveXFaceVisible = true;
    bool negativeXFaceVisible = true;
    bool positiveYFaceVisible = true;
    bool negativeYFaceVisible = true;
    bool positiveZFaceVisible = true;
    bool negativeZFaceVisible = true;
    unsigned int vertexCount = 0;
    const render::Texture *texture;
    unsigned int vertexBuffer;

    // TODO: Move block constructor to block.cpp
    // For some reason, doing so causes strange errors so it will be defined in the header for now
    inline Block(glm::vec3 position, render::assetLoader::TextureName texture = render::assetLoader::TextureName::MISSING_TEXTURE)
        : position{position}, texture{render::assetLoader::getTexture(texture)}
    {
      glGenBuffers(1, &this->vertexBuffer);
    }

    void initVertexBuffer();
};

class GrassBlock : public Block
{
  public:
    GrassBlock(glm::vec3 position) : Block{position, render::assetLoader::TextureName::GRASS} {}
};

class DirtBlock : public Block
{
  public:
    DirtBlock(glm::vec3 position) : Block{position, render::assetLoader::TextureName::DIRT} {}
};

class Chunk
{
  public:
    Chunk(glm::vec2 position, std::array<std::array<std::array<Block *, 16>, 16>, 16>);
    void draw(render::Shader shader);
    void updateBlockVisibility();
    glm::vec2 position;
    std::array<std::array<std::array<Block *, 16>, 16>, 16> blocks;
    unsigned int vertexArray;
};

[[nodiscard]] Chunk generateChunk(unsigned int seed, glm::vec2 position);
[[nodiscard]] std::vector<world::Chunk> generateTerrain(unsigned int seed, glm::vec2 worldSize);
} // namespace world