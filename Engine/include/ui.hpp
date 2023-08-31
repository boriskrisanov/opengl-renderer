#pragma once

#include <memory>
#include "camera.hpp"

namespace ui
{
	void init(GLFWwindow* window, std::shared_ptr<const render::Camera> camera);
	void update(GLFWwindow* window, bool& isWireframeDrawEnabled, bool& isCursorEnabled, float frameTimeInSeconds);
}