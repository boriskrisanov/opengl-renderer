#pragma once

#include "render/camera.hpp"
#include "render/render.hpp"
#include <functional>
#include <memory>

namespace ui
{
void init(GLFWwindow *window, std::shared_ptr<const render::Camera> camera);
void update(GLFWwindow *window, bool &isWireframeDrawEnabled, bool &isCursorEnabled, float frameTimeInSeconds);
void addWidget(std::function<void()> drawCallback);
} // namespace ui