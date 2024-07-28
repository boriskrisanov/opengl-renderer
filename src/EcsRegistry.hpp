#pragma once

#include "Scene.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "utils.hpp"
#include <functional>

class Scene;

class EcsRegistry
{
  public:
    explicit EcsRegistry(Scene& scene);
    void addSystem(const std::function<void(EcsRegistry &ecsRegistry)> &updateHandler);
    [[nodiscard]] vector<GameObject*> getGameObjects() const;
    [[nodiscard]] Scene &getScene() const;
    void addGameObject(GameObject* gameObject);
    void update();

  private:
    vector<GameObject*> gameObjects;
    vector<std::function<void(EcsRegistry &ecsRegistry)>> systemHandlers;
    Scene& scene;
};
