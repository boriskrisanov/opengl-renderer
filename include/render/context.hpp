#pragma once

#include "glm/vec2.hpp"
#include <memory>
#include <vector>
#include "gameObject.hpp"
#include "skybox.hpp"
#include <GLFW/glfw3.h>
#include <functional>

namespace render
{
struct RenderContext
{
    GLFWwindow *window;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    glm::vec2 windowSize;
    bool isWireframeDrawEnabled = false;
    bool isCursorEnabled = false;
    double frameTimeInMilliseconds = 0;
    std::shared_ptr<Skybox> skybox;
    std::vector<GameObject> gameObjects;
    Shader shader;
    std::shared_ptr<Camera> camera;
    std::function<void()> initScene;
    std::function<void()> updateScene;

    inline void updateDeltaTime()
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
};
} // namespace render