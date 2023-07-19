#pragma once

#include "render.hpp"
#include <functional>
#include <memory>


namespace ui
{
void init(GLFWwindow *window);
void update(GLFWwindow *window, bool &isCursorEnabled, double &secondsUntilNextCursorStateUpdate, float SECONDS_BETWEEN_CURSOR_STATE_UPDATES, float frameTimeInMilliseconds, std::shared_ptr<const render::Camera> camera, const std::function<void()> &regenerateTerrainClicked);
} // namespace ui