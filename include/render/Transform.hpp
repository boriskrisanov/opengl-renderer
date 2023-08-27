#pragma once

#include "Scale.hpp"

namespace render
{
struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    Scale scale;
};
} // namespace math