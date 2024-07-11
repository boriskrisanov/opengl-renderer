#pragma once

#include "utils.hpp"
#include <map>

using std::map;

class Shader
{
  public:
    explicit Shader(const string &name, const vector<string> &uniforms = {});
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] int getUniformLocation(const string &uniform) const;
    void select() const;

  private:
    unsigned int id;
    map<string, int> uniformLocations;
    string name;

    void createShaderProgram(const vector<unsigned int> &shaders);
};
