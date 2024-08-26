#pragma once

#include "Shader.hpp"
#include "input.hpp"
#include "math.hpp"
#include "utils.hpp"
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
    InputManager input{window};

  private:
    Vector2<int> windowSize;
};
