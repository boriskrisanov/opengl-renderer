#pragma once

#include <string>

namespace render
{
class Texture
{
  public:
    void select() const;
    Texture(std::string path);
    Texture(): Texture{"assets/textures/uv_grid_256.jpg"} {}

  private:
    unsigned int id;
};
} // namespace render