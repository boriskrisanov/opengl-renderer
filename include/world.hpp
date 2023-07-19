#pragma once

#include "glm/glm.hpp"
#include "render.hpp"

namespace world
{
class Block : public render::GameObject
{
  public:
    glm::vec3 position;
    Block(glm::vec3 position, render::assetLoader::TextureName texture = render::assetLoader::TextureName::MISSING_TEXTURE);

  private:
    unsigned int vertexArray;
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
    Chunk(glm::vec2 position, std::vector<std::shared_ptr<Block>> blocks);
    void draw(render::Shader shader);
    void updateBlockVisibility();
    glm::vec2 position;
    std::vector<std::shared_ptr<Block>> blocks;
};

[[nodiscard]] Chunk generateChunk(unsigned int seed, glm::vec2 position);
[[nodiscard]] std::vector<world::Chunk> generateTerrain(unsigned int seed, glm::vec2 worldSize);
} // namespace world