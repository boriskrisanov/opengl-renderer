#include "utils.hpp"
#include "world.hpp"
#include <PerlinNoise.hpp>

// TODO: Fix memory leak after terrain regeneration
std::vector<world::Chunk> world::generateTerrain(unsigned int seed, glm::vec2 worldSize)
{
    DEBUG_LOG("Started terrain generation with seed " << seed);

    std::vector<world::Chunk> chunks;

    // for (int x = 0; x < worldSize.x; x++)
    // {
    //     for (int y = 0; y < worldSize.y; y++)
    //     {
    //         chunks.push_back(world::generateChunk(seed, {x, y}));
    //     }
    // }

    chunks.push_back(world::generateChunk(seed, {0, 0}));

    DEBUG_LOG("Finished terrain generation");

    return chunks;
}

world::Chunk world::generateChunk(unsigned int seed, glm::vec2 position)
{
    std::array<std::array<std::array<Block *, 16>, 16>, 16> blocks;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                blocks[x][y][z] = nullptr;
            }
        }
    }

    const siv::PerlinNoise perlinNoise{seed};

    // Surface layer
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                blocks[x][y][z] = new GrassBlock{{x, y, z}};
            }
            // const double yHeight = perlinNoise.octave2D(x * 0.1, z * 0.1, 16);
        }
    }

    // std::vector<std::shared_ptr<Block>> blocks2;

    // Generate terrain in y direction
    // for (auto block : blocks)
    // {
    //     for (float y = block->position.y; y > -5; y -= 0.5)
    //     {
    //         blocks2.push_back(std::make_shared<DirtBlock>(glm::vec3{block->position.x, y, block->position.z}));
    //     }
    // }

    // for (auto block : blocks2)
    // {
    //     blocks.push_back(block);
    // }

    return Chunk{position, blocks};
}