#pragma once

#include "Skybox.hpp"
#include "Renderer.hpp"
#include "EcsRegistry.hpp"
#include "utils.hpp"

class EcsRegistry;

class Scene
{
  public:
    explicit Scene(Renderer& renderer);
    void update();
    [[nodiscard]] EcsRegistry& getEcsRegistry() const;
    [[nodiscard]] Renderer &getRenderer() const;
    shared_ptr<Skybox> skybox = make_shared<Skybox>();

  private:
    unique_ptr<EcsRegistry> ecsRegistry = make_unique<EcsRegistry>(*this);
    Renderer& renderer;
};
