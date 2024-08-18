#pragma once

#include "Shader.hpp"
#include "math.hpp"
#include "utils.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
  public:
    explicit Renderer(Vector2<int> windowSize);
    ~Renderer();
    [[nodiscard]] bool isWindowClosed() const;
    [[nodiscard]] Vector2<int> getWindowSize() const;
    unique_ptr<Shader> shader;
    GLFWwindow *window;

  private:
    Vector2<int> windowSize;
};
