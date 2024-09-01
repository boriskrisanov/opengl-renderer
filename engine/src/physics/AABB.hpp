#pragma once

#include "../math.hpp"
#include <array>

/*
 * Axis aligned bounding box
 */
class AABB
{
  public:
    explicit AABB(const std::vector<Vector3<>>& vertexes);
    [[nodiscard]] bool intersects(Vector3<> rayStart, Vector3<> directionVector) const;
    std::array<Vector3<>, 8> points;
    std::array<std::array<Vector3<>, 4>, 6> faces;
  private:
    Vector3<> min;
    Vector3<> max;
};
