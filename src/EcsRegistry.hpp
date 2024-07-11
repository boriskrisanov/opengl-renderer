#pragma once

#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "utils.hpp"
#include <functional>

class EcsRegistry
{
  public:
    explicit EcsRegistry(const Renderer &renderer, Shader& shader) : renderer{renderer}, shader{shader} {}
    void addSystem(const std::function<void(const EcsRegistry &registry)> &updateHandler);
    [[nodiscard]] vector<GameObject*> getGameObjects() const;
    void addGameObject(GameObject* gameObject);
    void update();
    const Renderer &renderer;
    // TODO: This shouldn't really be handled by ECS but for now it's the simplest way to access shader uniforms in the render system
    const Shader& shader;

  private:
    vector<GameObject*> gameObjects;
    vector<std::function<void(const EcsRegistry &registry)>> systemHandlers;
};
