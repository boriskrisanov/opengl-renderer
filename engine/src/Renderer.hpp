#pragma once

#include "Shader.hpp"
#include "input.hpp"
#include "math.hpp"
#include "utils.hpp"
#include <GLFW/glfw3.h>
#include <memory>

class Renderer
{
  public:
    explicit Renderer(Vector2<int> windowSize);
    ~Renderer();
    [[nodiscard]] bool isWindowClosed() const;
    [[nodiscard]] Vector2<int> getWindowSize() const;
    std::unique_ptr<Shader> shader;
    GLFWwindow *window;
    InputManager input{window};

  private:
    Vector2<int> windowSize;
};
