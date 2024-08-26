#pragma once

#include "EcsRegistry.hpp"
#include "Renderer.hpp"
#include "Skybox.hpp"
#include "utils.hpp"
#include <memory>

class EcsRegistry;

class Scene
{
  public:
    explicit Scene(Renderer &renderer);
    void update();
    [[nodiscard]] EcsRegistry &getEcsRegistry() const;
    [[nodiscard]] Renderer &getRenderer() const;
    std::shared_ptr<Skybox> skybox = std::make_shared<Skybox>();

  private:
    std::unique_ptr<EcsRegistry> ecsRegistry = std::make_unique<EcsRegistry>(*this);
    Renderer &renderer;
};
