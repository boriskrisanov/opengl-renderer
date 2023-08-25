#pragma once

#include "glm/glm.hpp"
#include "render/render.hpp"
#include "render/assets.hpp"
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
    const std::array<float, 5 * 6> negativeZFaceVertexes = {
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f
    };
    const std::array<float, 5 * 6> positiveZFaceVertexes = {
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f
    };
    const std::array<float, 5 * 6> negativeYFaceVertexes = {
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f
    };
    const std::array<float, 5 * 6> positiveYFaceVertexes = {
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // clang-format on

    glm::vec3 position;
    bool positiveXFaceVisible = false;
    bool negativeXFaceVisible = false;
    bool positiveYFaceVisible = false;
    bool negativeYFaceVisible = false;
    bool positiveZFaceVisible = false;
    bool negativeZFaceVisible = false;
    unsigned int vertexCount = 0;
    const render::Texture *texture;
    unsigned int vertexBuffer;

    // TODO: Move block constructor to block.cpp
    // For some reason, doing so causes strange errors so it will be defined in the header for now
    inline Block(glm::vec3 position, render::assetLoader::TextureName texture = render::assetLoader::TextureName::MISSING_TEXTURE)
        : position{position}, texture{render::assetLoader::getTexture(texture)}
    {
    }

    void initVertexBuffer();
    // unsigned int positiveXFaceBuffer;
    // unsigned int negativeXFaceBuffer;
    // unsigned int positiveYFaceBuffer;
    // unsigned int negativeYFaceBuffer;
    // unsigned int positiveZFaceBuffer;
    // unsigned int negativeZFaceBuffer;

    // inline void initBuffer(unsigned int *buffer, std::array<float, 6 * 5> data)
    // {
    //     glGenBuffers(1, buffer);
    //     glBindBuffer(GL_ARRAY_BUFFER, *buffer);

    //     glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data, GL_STATIC_DRAW);

    //     // Position
    //     glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);
    //     glEnableVertexAttribArray(0);

    //     // Texture coordinate
    //     glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (const void *)(3 * sizeof(float)));
    //     glEnableVertexAttribArray(1);
    // }

    // inline void draw()
    // {
    //     if (positiveXFaceVisible)
    //     {
    //         glBindBuffer(GL_ARRAY_BUFFER, positiveXFaceBuffer);
    //         glDrawArrays(GL_TRIANGLES, 0, 6);
    //     }
    //     if (negativeXFaceVisible)
    //     {
    //         glBindBuffer(GL_ARRAY_BUFFER, negativeXFaceBuffer);
    //         glDrawArrays(GL_TRIANGLES, 0, 6);
    //     }

    //     if (positiveZFaceVisible)
    //     {
    //         glBindBuffer(GL_ARRAY_BUFFER, positiveZFaceBuffer);
    //         glDrawArrays(GL_TRIANGLES, 0, 6);
    //     }
    //     if (negativeZFaceVisible)
    //     {
    //         glBindBuffer(GL_ARRAY_BUFFER, negativeZFaceBuffer);
    //         glDrawArrays(GL_TRIANGLES, 0, 6);
    //     }
    // }
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