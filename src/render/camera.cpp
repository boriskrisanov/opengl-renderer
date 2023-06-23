#include "defs.hpp"

using glm::cross;
using glm::mat4;
using glm::normalize;
using glm::perspective;
using glm::radians;
using glm::vec2;
using glm::vec3;

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

    // TODO: Move glGetUniformLocation calls to constructor
    // int viewMatrixLocation = glGetUniformLocation(shader.id, "viewMatrix");
    // glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));

    shader.setUniform("viewMatrix", viewMatrix);

    // int projectionMatrixLocation = glGetUniformLocation(shader.id, "projectionMatrix");
    // glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));

    shader.setUniform("projectionMatrix", projectionMatrix);
}

void Camera::respondToKeyboardInput()
{
    if (input::isKeyDown(window, input::W))
    {
        position += speed * front;
    }
    if (input::isKeyDown(window, input::S))
    {
        position -= speed * front;
    }
    if (input::isKeyDown(window, input::A))
    {
        position -= speed * normalize(cross(front, up));
    }
    if (input::isKeyDown(window, input::D))
    {
        position += speed * normalize(cross(front, up));
    }
    if (input::isKeyDown(window, input::Q))
    {
        position -= speed * up;
    }
    if (input::isKeyDown(window, input::E))
    {
        position += speed * up;
    }
}

void Camera::respondToMouseInput()
{
    auto mousePosition = input::getMousePosition(window);
    const double sensitivity = 0.07;

    mouseOffset = vec2(mousePosition.x - lastMousePosition.x, lastMousePosition.y - mousePosition.y);
    lastMousePosition = mousePosition;

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

void Camera::update()
{
    this->respondToMouseInput();
    this->respondToKeyboardInput();
    this->updateMatrixUniforms();
}
} // namespace render