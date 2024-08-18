#include "input.hpp"
#include <GLFW/glfw3.h>

using glm::vec2;

namespace input
{
bool isKeyDown(GLFWwindow *window, Key key)
{
    const int keyState = glfwGetKey(window, (int)key);
    return keyState == GLFW_PRESS;
}

Vector2<> getMousePosition(GLFWwindow *window)
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}
} // namespace input