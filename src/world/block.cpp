#include <defs.hpp>

using glm::vec3;

namespace world
{
using enum render::assetLoader::ModelName;
using enum render::assetLoader::TextureName;

Block::Block(vec3 position) : render::GameObject({position.x / 2, position.y, position.z / 2}, {0, 0, 0}, CUBE, MISSING_TEXTURE, 0.25)
{
	this->position = position;
}
} // namespace world