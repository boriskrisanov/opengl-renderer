#include "defs.hpp"

namespace world
{
Chunk::Chunk(glm::vec2 position, std::vector<Block> blocks)
    : position{position}, blocks{blocks}
{
}

void Chunk::draw(render::Shader shader)
{
    for (auto block : this->blocks)
    {
        block.render(shader);
    }
}
} // namespace world