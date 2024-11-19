#pragma once
#include "EcsRegistry.hpp"

#include <GLFW/glfw3.h>

namespace ui
{
    void init(GLFWwindow* window);
    void update();
    void endUpdate();
    void shutdown();
    void updateUISystem(const EcsRegistry &ecsRegistry);
}