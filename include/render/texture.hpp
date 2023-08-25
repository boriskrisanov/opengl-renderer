#pragma once

#include <string>

namespace render
{
class Texture
{
  public:
    void select() const;
    Texture(std::string path);

  private:
    unsigned int id;
};
} // namespace render