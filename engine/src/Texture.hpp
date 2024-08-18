#pragma once

#include "utils.hpp"

class Texture
{
  public:
    void select() const;
    Texture(string path);

  private:
    unsigned int id;
};
