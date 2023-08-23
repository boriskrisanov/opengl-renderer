#pragma once

#include "render.hpp"
#include <vector>

namespace render
{
	class Scene
	{
		public:
			Scene(std::vector<GameObject> gameObjects) : gameObjects{gameObjects} {}
			std::vector<GameObject> gameObjects;
			void draw();
	};
}