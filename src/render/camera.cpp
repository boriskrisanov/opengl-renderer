#include "render/camera.hpp"
#include "input.hpp"
#include <algorithm>

using glm::cross, glm::mat4, glm::normalize, glm::perspective, glm::radians, glm::vec2, glm::vec3;

namespace render
{
Camera::Camera(GLFWwindow *window, vec2 windowSize, render::Shader shader, float speed) : projectionMatrix{perspective(radians(this->fov), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f)},
                                                                                          speed{speed},
                                                                                          window{window},
                                                                                          shader{shader}
{
}

void Camera::updateMatrixUniforms()
{
    viewMatrix = glm::lookAt(position, position + front, up);

    shader.setUniform("viewMatrix", viewMatrix);
    shader.setUniform("projectionMatrix", projectionMatrix);
}

void Camera::respondToKeyboardInput(float deltaTime)
{
    if (input::isKeyDown(window, input::W))
    {
        position += speed * front * deltaTime;
    }
    if (input::isKeyDown(window, input::S))
    {
        position -= speed * front * deltaTime;
    }
    if (input::isKeyDown(window, input::A))
    {
        position -= speed * normalize(cross(front, up)) * deltaTime;
    }
    if (input::isKeyDown(window, input::D))
    {
        position += speed * normalize(cross(front, up)) * deltaTime;
    }
    if (input::isKeyDown(window, input::Q))
    {
        position -= speed * up * deltaTime;
    }
    if (input::isKeyDown(window, input::E))
    {
        position += speed * up * deltaTime;
    }
}

void Camera::respondToMouseInput()
{
    const vec2 currentMousePosition = input::getMousePosition(window);
    const double sensitivity = 0.07;

    mouseOffset = vec2{currentMousePosition.x - lastMousePosition.x, lastMousePosition.y - currentMousePosition.y};
    lastMousePosition = currentMousePosition;

    mouseOffset *= sensitivity;

    yaw += mouseOffset.x;
    pitch += mouseOffset.y;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    direction = vec3(
        cos(radians(yaw)) * cos(radians(pitch)),
        sin(radians(pitch)),
        sin(radians(yaw)) * cos(radians(pitch)));

    front = normalize(direction);
}

void Camera::update(float deltaTime)
{
    this->respondToMouseInput();
    this->respondToKeyboardInput(deltaTime);
    this->updateMatrixUniforms();
}
} // namespace render