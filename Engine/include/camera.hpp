#pragma once

#include <glm/glm.hpp>
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include "WindowSize.hpp"

namespace render
{
class Camera
{
  public:
    Camera(GLFWwindow *window, WindowSize windowSize, render::Shader shader, float speed);
    glm::vec3 position = glm::vec3{ 0, 0, 0 };
    float fov = 80;
    glm::mat4 projectionMatrix{};
    glm::mat4 viewMatrix{};
    void update(float deltaTime);

  private:
    void updateMatrixUniforms();
    void respondToKeyboardInput(float deltaTime);
    void respondToMouseInput();
    glm::vec3 target{0, 0, 0};
    glm::vec3 direction{glm::normalize(position - target)};
    glm::vec3 up{0, 1, 0};
    glm::vec3 front{0, 0, -1};
    float speed;
    float pitch = 0;
    float yaw = -90;
    glm::vec2 lastMousePosition = glm::vec2{ 0, 0 };
    glm::vec2 mouseOffset = glm::vec2{0, 0};
    GLFWwindow *window;
    render::Shader shader;
};
}