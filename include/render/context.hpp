#pragma once

#include "glm/vec2.hpp"
#include <memory>
#include <vector>
#include "gameObject.hpp"
#include "skybox.hpp"
#include <GLFW/glfw3.h>

namespace render
{
struct RenderContext
{
    GLFWwindow *window;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec2 windowSize;
    bool isWireframeDrawEnabled = false;
    double frameTimeInMilliseconds = 0;
    std::shared_ptr<Skybox> skybox;
    std::vector<GameObject> gameObjects;
};
} // namespace render