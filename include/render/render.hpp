#pragma once

#include "shader.hpp"
#include "GLFW/glfw3.h"

namespace render
{
GLFWwindow *initAndCreateWindow();
void drawFrame(render::Shader shader);
void setWireframeDrawEnabled(bool enabled);
void initCamera(render::Shader shader);
void setVsyncEnabled(bool enabled);
void initScene();

} // namespace render