#pragma once

#include <glm/vec3.hpp>

namespace render
{
class Scale
{
  public:
    Scale(float scale) : x{scale}, y{scale}, z{scale} {}
    Scale(glm::vec3 scale) : x{scale.x}, y{scale.y}, z{scale.z} {}
    const float x;
    const float y;
    const float z;
};
} // namespace render