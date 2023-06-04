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
Camera::Camera(GLFWwindow *window, vec2 windowSize, unsigned int shaderProgram, float speed)
{
    mat4 projectionMatrix = perspective(radians(45.0f), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);
    mat4 modelMatrix = rotate(mat4(1.0f), 0.0f, vec3(1.0f, 0.0f, 0.0f));
    vec3 position = vec3(0, 0, 0);
    vec3 target = vec3(0.0f, 0.0f, 0.0f);
    vec3 direction = normalize(position - target);
    vec3 up = vec3(0, 1, 0); // cross(direction, right);
    vec3 front = vec3(0.0f, 0.0f, -1.0f);
    mat4 viewMatrix{};

    this->projectionMatrix = projectionMatrix;
    this->modelMatrix = modelMatrix;
    this->viewMatrix = viewMatrix;
    this->position = position;
    this->target = target;
    this->direction = direction;
    this->up = up;
    this->front = front;
    this->shaderProgram = shaderProgram;
    this->speed = speed;
    this->window = window;
}

void Camera::updateMatrixUniforms()
{
    viewMatrix = glm::lookAt(position, position + front, up);

    int modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));

    int viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));

    int projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));
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

    /*
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    vec3 right = glm::normalize(glm::cross(front, up));
    up = glm::normalize(glm::cross(right, front));
    */

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