#include "defs.hpp"
#include <GLFW/glfw3.h>

using glm::vec2;

namespace input
{
bool isKeyDown(GLFWwindow *window, Key key)
{
    int keyState = glfwGetKey(window, key);
    return keyState == GLFW_PRESS;
}

vec2 getMousePosition(GLFWwindow *window)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return vec2{x, y};
}
} // namespace input