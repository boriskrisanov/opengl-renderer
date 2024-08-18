#pragma once

#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include "math.hpp"

namespace input
{

enum class Key : int
{
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    Q = GLFW_KEY_Q,
    E = GLFW_KEY_E,
    ESCAPE = GLFW_KEY_ESCAPE
};

[[nodiscard]] bool isKeyDown(GLFWwindow *window, Key key);
[[nodiscard]] Vector2<> getMousePosition(GLFWwindow *window);
} // namespace input