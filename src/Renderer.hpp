#pragma once

#include "utils.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math.hpp"

class Renderer
{
  public:
    explicit Renderer(Vector2<int> windowSize);
    ~Renderer();
    [[nodiscard]] bool isWindowClosed() const;
    [[nodiscard]] Vector2<int> getWindowSize() const;
    GLFWwindow *window;

  private:
    Vector2<int> windowSize;
};
