#include <defs.hpp>

using glm::vec3;

namespace world
{
Block::Block(vec3 position) : render::Cube({position.x / 2, position.y, position.z / 2}, {0, 0, 0}, render::assetLoader::getTexture(render::assetLoader::TextureName::CONTAINER))
{
	this->position = position;
}
} // namespace world