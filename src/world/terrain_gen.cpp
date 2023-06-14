#include "defs.hpp"
#include "PerlinNoise.hpp"

using render::Cube;

// TODO: Seed selector and random seed generation
const siv::PerlinNoise::seed_type seed = 123;
const siv::PerlinNoise perlinNoise{seed};

world::Chunk world::generateChunk(glm::vec2 position)
{
    std::vector<std::shared_ptr<Cube>> cubes;

    render::Texture texture{"assets/textures/container.jpg"};

    for (float x = position.x; x < 16 + position.x; x += 0.5)
    {
        for (float z = position.y; z < 16 + position.y; z += 0.5)
        {
            const double yHeight = perlinNoise.octave2D_01(x, z, 4);
            cubes.push_back(std::make_shared<Cube>(Cube{{x, round(yHeight) / 2, z}, {0, 0, 0}, texture}));
        }
    }

    return Chunk{position, cubes};
};