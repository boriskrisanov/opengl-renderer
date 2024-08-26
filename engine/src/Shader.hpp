#pragma once

#include "utils.hpp"
#include <map>

class Shader
{
  public:
    explicit Shader(const std::string &name, const std::vector<std::string> &uniforms = {});
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] int getUniformLocation(const std::string &uniform) const;
    void select() const;
    ~Shader();

  private:
    unsigned int id;
    std::map<std::string, int> uniformLocations;
    std::string name;

    void createShaderProgram(const std::vector<unsigned int> &shaders);
};
