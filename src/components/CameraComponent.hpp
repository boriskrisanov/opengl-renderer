#pragma once

#include "../Component.hpp"
#include "../math.hpp"

struct CameraComponent : public Component
{
    explicit CameraComponent(Vector2<int> windowSize);
    double speed = 0.5;
    double fov = 80;
    double pitch = 0;
    double yaw = -90;
    double sensitivity = 0.05;
    Vector2<> mouseOffset{0, 0};
    Vector2<> lastMousePosition{0, 0};
    Vector3<> direction{};
    Vector3<> front{0, 0, -1};
    Vector3<> up{0, 1, 0};
    glm::mat4 projectionMatrix{1};
};
