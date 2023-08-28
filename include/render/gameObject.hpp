#pragma once

#include "Transform.hpp"
#include "assets.hpp"
#include "render/model.hpp"
#include "Scale.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>


using glm::vec3;

namespace render
{
class GameObject
{
  public:
    GameObject(Model model, Transform transform = {
                   .position = {0, 0, 0},
                   .rotation = {0, 0, 0},
                   .scale = 1});

    virtual void onStart() = 0;
    virtual void onUpdate() = 0;

    void draw(render::Shader shader) const;

    Transform transform;

  protected:
    const Model model;
  private:
    unsigned int vertexBufferId;
    unsigned int vertexArrayId;
};
} // namespace render