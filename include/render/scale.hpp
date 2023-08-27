#pragma once

#include <glm/glm.hpp>

namespace render
{
class Scale
{
  public:
    Scale(double scale) : x{scale}, y{scale}, z{scale} {}
    Scale(glm::vec3 scale) : x{scale.x}, y{scale.y}, z{scale.z} {}
    const double x;
    const double y;
    const double z;
};
} // namespace render