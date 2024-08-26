#pragma once

#include "math.hpp"
#include <GLFW/glfw3.h>

class InputManager
{
  public:
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

    explicit InputManager(GLFWwindow *&window);

    [[nodiscard]] bool isKeyDown(Key key) const;
    [[nodiscard]] Vector2<> getMousePosition() const;
    void setCursorEnabled(bool isEnabled) const;
    [[nodiscard]] bool isCursorEnabled() const;

  private:
    GLFWwindow *&window;
};