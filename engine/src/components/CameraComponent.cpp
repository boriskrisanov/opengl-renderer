#include "CameraComponent.hpp"
#include <glm/ext.hpp>

CameraComponent::CameraComponent(Vector2<int> windowSize)
{
    double aspectRatio = (double) windowSize.x / (double) windowSize.y;
    projectionMatrix = glm::perspective(radians(fov), aspectRatio, 0.1, 100.0);
}
