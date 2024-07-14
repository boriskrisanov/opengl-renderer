#pragma once

#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "utils.hpp"
#include <functional>

class EcsRegistry
{
  public:
    explicit EcsRegistry(const Renderer &renderer, Shader& shader, Skybox* skybox) : renderer{renderer}, shader{shader}, skybox{skybox} {}
    void addSystem(const std::function<void(const EcsRegistry &registry)> &updateHandler);
    [[nodiscard]] vector<GameObject*> getGameObjects() const;
    void addGameObject(GameObject* gameObject);
    void update();
    const Renderer &renderer;
    // TODO: This shouldn't really be handled by ECS but for now it's the simplest way to access shader uniforms in the render system
    const Shader& shader;
    // TODO: Again, this should probably be a global scene property and not an ECS property, maybe this should be a camera property?
    // TODO: Should probably use optional instead of nullptr for no skybox
    Skybox* skybox;

  private:
    vector<GameObject*> gameObjects;
    vector<std::function<void(const EcsRegistry &registry)>> systemHandlers;
};
