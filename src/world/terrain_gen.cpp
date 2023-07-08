#include "defs.hpp"

// TODO: Fix memory leak after terrain regeneration
std::vector<world::Chunk> world::generateTerrain(unsigned int seed, glm::vec2 worldSize)
{
    DEBUG_LOG("Started terrain generation with seed " << seed);

    std::vector<world::Chunk> chunks;

    for (int x = 0; x < worldSize.x; x++)
    {
        for (int y = 0; y < worldSize.y; y++)
        {
            chunks.push_back(world::generateChunk(seed, {x, y}));
        }
    }

    DEBUG_LOG("Finished terrain generation");

    return chunks;
}

world::Chunk world::generateChunk(unsigned int seed, glm::vec2 position)
{
    std::vector<Block> blocks;
    const siv::PerlinNoise perlinNoise{seed};

    // Surface layer
    for (int x = 16 * position.x; x < 16 + 16 * position.x; x++)
    {
        for (int z = 16 * position.y; z < 16 + 16 * position.y; z++)
        {
            const double yHeight = perlinNoise.octave2D(x * 0.1, z * 0.1, 16) * 4;
            const GrassBlock block{{x, round(yHeight) / 2, z}};
            blocks.push_back(block);
        }
    }

    std::vector<Block> blocks2;

    // Generate terrain in y direction
    for (auto block : blocks)
    {
        for (float y = block.position.y; y > -5; y -= 0.5)
        {
            const DirtBlock newBlock{{block.position.x, y, block.position.z}};
            blocks2.push_back(newBlock);
        }
    }

    for (auto block : blocks2)
    {
        blocks.push_back(block);
    }

    return Chunk{position, blocks};
};