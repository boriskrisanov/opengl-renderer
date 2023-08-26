#pragma once

#include "shader.hpp"
#include "GLFW/glfw3.h"
#include "context.hpp"

namespace render
{
[[nodiscard]] RenderContext initAndCreateWindow(glm::vec2 windowSize, std::function<void()> onStart, std::function<void(float deltaTime)> onUpdate);
void drawFrame(render::Shader shader);
void setWireframeDrawEnabled(bool enabled);
void setVsyncEnabled(bool enabled);
void runMainLoop(RenderContext context);
void addGameObject(GameObject gameObject);
} // namespace render