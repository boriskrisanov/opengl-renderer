#include <defs.hpp>

using glm::vec3;

namespace world
{
using enum render::assetLoader::ModelName;
using enum render::assetLoader::TextureName;

Block::Block(vec3 position, render::assetLoader::TextureName texture) : render::GameObject({position.x / 2, position.y, position.z / 2}, {0, 0, 0}, CUBE, texture, 0.25), position{position}
{
	
}
} // namespace world