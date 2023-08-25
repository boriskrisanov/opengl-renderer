#pragma once

#include "shader.hpp"
#include "GLFW/glfw3.h"
#include "context.hpp"

namespace render
{
RenderContext initAndCreateWindow(glm::vec2 windowSize, std::function<void()> onStart, std::function<void()> onUpdate);
void drawFrame(render::Shader shader);
void setWireframeDrawEnabled(bool enabled);
void setVsyncEnabled(bool enabled);
void runMainLoop(RenderContext context);
} // namespace render