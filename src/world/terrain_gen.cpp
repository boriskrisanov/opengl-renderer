#include "defs.hpp"

using render::Cube;

world::Chunk world::generateChunk(glm::vec2 position)
{
    std::vector<Cube> cubes;

    render::Texture texture{"assets/textures/container.jpg"};

    for (int x = position.x; x < 16 + position.x; x++)
    {
        for (int z = position.y; z < 16 + position.y; z++)
        {
            for (int y = 0; y < 1; y++)
            {
                cubes.push_back({{x, y, z}, {0, 0, 0}, texture});
            }
        }
    }

    return Chunk{position, cubes};
};