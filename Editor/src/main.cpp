#include <iostream>
#include "render.hpp"

int main()
{
	render::Renderer renderer{ {1920, 1080}, [] {}, [](float deltaTime) {} };

	renderer.begin();
}