#include "glm/gtc/matrix_transform.hpp"
#include "game/world/chunk.hpp"

namespace world
{
Chunk::Chunk(glm::vec2 position, std::array<std::array<std::array<Block *, 16>, 16>, 16> blocks)
    : position{position}, blocks{blocks}
{
    glGenVertexArrays(1, &this->vertexArray);
    this->updateBlockVisibility();
}

void Chunk::draw(render::Shader shader)
{
    glBindVertexArray(this->vertexArray);
 
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                const auto block = blocks[x][y][z];

                if (block == nullptr)
                {
                    continue;
                }

                block->texture->select();

                glm::mat4 transform{1};
                // transform = glm::translate(transform, {block->position.x, block->position.z, block->position.y});
                transform = glm::translate(transform, block->position);
                shader.setUniform("transform", transform);

                glDrawArrays(GL_TRIANGLES, 0, block->vertexCount);
                // block->draw();
            }
        }
    }
}

void Chunk::updateBlockVisibility()
{
    // TODO
    glBindVertexArray(this->vertexArray);

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                if (blocks[x][y][z] == nullptr)
                {
                    continue;
                }

                const bool hasAdjacentBlockInPositiveX = x != 15 && blocks[x + 1][y][z] != nullptr;
                const bool hasAdjacentBlockInNegativeX = x != 0 && blocks[x - 1][y][z] != nullptr;
                const bool hasAdjacentBlockInPositiveY = y != 15 && blocks[x][y + 1][z] != nullptr;
                const bool hasAdjacentBlockInNegativeY = y != 0 && blocks[x][y - 1][z] != nullptr;
                const bool hasAdjacentBlockInNegativeZ = z != 0 && blocks[x][y][z - 1] != nullptr;
                const bool hasAdjacentBlockInPositiveZ = z != 15 && blocks[x][y][z + 1] != nullptr;

                blocks[x][y][z]->positiveXFaceVisible = !hasAdjacentBlockInPositiveX;
                blocks[x][y][z]->negativeXFaceVisible = !hasAdjacentBlockInNegativeX;
                // blocks[x][y][z]->positiveYFaceVisible = !hasAdjacentBlockInPositiveY;
                // blocks[x][y][z]->negativeYFaceVisible = !hasAdjacentBlockInNegativeY;
                blocks[x][y][z]->positiveZFaceVisible = !hasAdjacentBlockInPositiveZ;
                blocks[x][y][z]->negativeZFaceVisible = !hasAdjacentBlockInNegativeZ;

                blocks[x][y][z]->initVertexBuffer();
            }
        }
    }
}
} // namespace world