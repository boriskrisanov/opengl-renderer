#pragma once

#include "glm/glm.hpp"
#include "render/render.hpp"
#include "render/assets.hpp"
#include <algorithm>
#include <array>
#include "chunk.hpp"

namespace world
{
[[nodiscard]] Chunk generateChunk(unsigned int seed, glm::vec2 position);
[[nodiscard]] std::vector<world::Chunk> generateTerrain(unsigned int seed, glm::vec2 worldSize);
} // namespace world