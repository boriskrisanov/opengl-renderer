#include "systems.hpp"
#include "../components/CameraComponent.hpp"
#include "../input.hpp"
#include <algorithm>

void updateCameraMovementSystem(const EcsRegistry &ecsRegistry)
{
    const Renderer& renderer = ecsRegistry.getScene().getRenderer();

    for (GameObject* gameObject : ecsRegistry.getGameObjects())
    {
        auto camera = gameObject->getComponent<CameraComponent>();
        if (camera == nullptr)
        {
            continue;
        }
        // TODO: Use deltaTime
        double deltaTime = 1;

        // Respond to mouse input
        Vector2 currentMousePosition = renderer.input.getMousePosition();

        camera->mouseOffset = currentMousePosition - camera->lastMousePosition;
        camera->lastMousePosition = currentMousePosition;

        camera->mouseOffset *= camera->sensitivity;

        camera->yaw += camera->mouseOffset.x;
        // Not sure why this needs to be -= because in the old code it was positive. Might be a bug in Vector2?
        camera->pitch -= camera->mouseOffset.y;

        camera->pitch = std::clamp(camera->pitch, -89.0, 89.0);

        // clang-format off
        camera->direction = Vector3{
            cos(radians(camera->yaw)) * cos(radians(camera->pitch)),
            sin(radians(camera->pitch)),
            sin(radians(camera->yaw)) * cos(radians(camera->pitch))
        };
        // clang-format on

        camera->front = camera->direction.normalised();

        // Respond to keyboard input

        if (renderer.input.isKeyDown(InputManager::Key::W))
        {
            gameObject->position += camera->speed * camera->front * deltaTime;
        }
        if (renderer.input.isKeyDown(InputManager::Key::S))
        {
            gameObject->position -= camera->speed * camera->front * deltaTime;
        }
        if (renderer.input.isKeyDown(InputManager::Key::A))
        {
            gameObject->position -= camera->speed * cross(camera->front, camera->up).normalised() * deltaTime;
        }
        if (renderer.input.isKeyDown(InputManager::Key::D))
        {
            gameObject->position += camera->speed * cross(camera->front, camera->up).normalised() * deltaTime;
        }
        if (renderer.input.isKeyDown(InputManager::Key::Q))
        {
            gameObject->position -= camera->speed * camera->up * deltaTime;
        }
        if (renderer.input.isKeyDown(InputManager::Key::E))
        {
            gameObject->position += camera->speed * camera->up * deltaTime;
        }
    }
}
