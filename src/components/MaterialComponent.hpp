#pragma once

#include "../Texture.hpp"

struct MaterialComponent : public Component
{
    explicit MaterialComponent(Texture texture) : texture{texture} {};
    Texture texture;
};
