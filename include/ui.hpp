#pragma once

#include "render/camera.hpp"
#include "render/render.hpp"
#include <functional>
#include <memory>

namespace ui
{
struct UIContext
{
    GLFWwindow *window;
    bool isCursorEnabled;
    float secondsUntilNextCursorStateUpdate;
    float secondsBetweenCursorStateUpdates;
    std::shared_ptr<const render::Camera> camera;
};

void init(GLFWwindow *window, std::shared_ptr<const render::Camera> camera);
void update(GLFWwindow *window, bool &isWireframeDrawEnabled, bool &isCursorEnabled, float frameTimeInSeconds, const std::function<void()> &regenerateTerrainClicked);
} // namespace ui