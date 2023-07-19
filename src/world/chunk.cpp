#include "world.hpp"

namespace world
{
Chunk::Chunk(glm::vec2 position, std::vector<std::shared_ptr<Block>> blocks)
    : position{position}, blocks{blocks}
{
    this->updateBlockVisibility();
}

void Chunk::draw(render::Shader shader)
{
    for (auto block : this->blocks)
    {
        block->render(shader);
    }
}

bool doesBlockWithPositionExist(std::vector<std::shared_ptr<Block>> blocks, glm::vec3 position)
{
    for (auto block : blocks)
    {
        if (block->position == position)
        {
            return true;
        }
    }

    return false;
}

void Chunk::updateBlockVisibility()
{
    DEBUG_LOG("Started for chunk " << this->position.x << ", " << this->position.y);

    for (auto block : this->blocks)
    {
        block->isVisible = true;
        continue;

        const glm::vec3 pos = block->position;

        // Find the position of the adjacent block in each direction
        const auto positiveX = glm::vec3{pos.x + 1, pos.y, pos.z};
        const auto negativeX = glm::vec3{pos.x - 1, pos.y, pos.z};

        const auto positiveY = glm::vec3{pos.x, pos.y + 1, pos.z};
        const auto negativeY = glm::vec3{pos.x, pos.y - 1, pos.z};

        const auto positiveZ = glm::vec3{pos.x, pos.y, pos.z + 1};
        const auto negativeZ = glm::vec3{pos.x, pos.y, pos.z - 1};

        const bool hasAdjacentBlockInEachDirection = doesBlockWithPositionExist(blocks, positiveX) &&
                                                     doesBlockWithPositionExist(blocks, negativeX) &&
                                                     doesBlockWithPositionExist(blocks, positiveY) &&
                                                     doesBlockWithPositionExist(blocks, negativeY) &&
                                                     doesBlockWithPositionExist(blocks, positiveZ) &&
                                                     doesBlockWithPositionExist(blocks, negativeZ);

        // TODO: Handle chunk borders
        // Likely because most blocks are inside chunks
        if (hasAdjacentBlockInEachDirection) [[likely]]
        {
            block->isVisible = false;
        }
    }

    DEBUG_LOG("Finished for chunk " << this->position.x << ", " << this->position.y);
}
} // namespace world