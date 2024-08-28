#pragma once

#include "utils.hpp"
#include "math.hpp"
#include <map>

class Shader
{
  public:
    explicit Shader(const std::string &name, const std::vector<std::string> &uniforms = {});
    ~Shader();
    [[nodiscard]] unsigned int getId() const;
    [[nodiscard]] int getUniformLocation(const std::string &uniform) const;
    void select() const;
    void setUniform(const std::string &uniform, glm::mat4 value) const;
    void setUniform(const std::string &uniform, Vector3<float> value) const;

  private:
    unsigned int id;
    std::map<std::string, int> uniformLocations;
    std::string name;

    void createShaderProgram(const std::vector<unsigned int> &shaders);
};

