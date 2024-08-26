#include "input.hpp"

InputManager::InputManager(GLFWwindow *&window)
    : window{window}
{
}

bool InputManager::isKeyDown(Key key) const
{
    const int keyState = glfwGetKey(window, (int)key);
    return keyState == GLFW_PRESS;
}

Vector2<> InputManager::getMousePosition() const
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}

void InputManager::setCursorEnabled(bool isEnabled) const
{
    glfwSetInputMode(window, GLFW_CURSOR, isEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

bool InputManager::isCursorEnabled() const
{
    return glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}
