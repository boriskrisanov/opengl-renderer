#pragma once

#include "utils.hpp"

class Texture
{
  public:
    void select() const;
    explicit Texture(std::string path);

  private:
    unsigned int id;
};
