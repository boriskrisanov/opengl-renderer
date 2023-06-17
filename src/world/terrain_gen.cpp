#include "defs.hpp"

using render::Cube;

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
    std::vector<std::shared_ptr<Cube>> cubes;
    const siv::PerlinNoise perlinNoise{seed};

    render::Texture texture{"assets/textures/container.jpg"};

    for (float x = 16 * position.x; x < 16 + 16 * position.x; x += 0.5)
    {
        for (float z = 16 * position.y; z < 16 + 16 * position.y; z += 0.5)
        {
            const double yHeight = perlinNoise.octave2D(x * 0.1, z * 0.1, 16) * 4;
            cubes.push_back(std::make_shared<Cube>(Cube{{x, round(yHeight) / 2, z}, {0, 0, 0}, texture}));
        }
    }

    return Chunk{position, cubes};
};