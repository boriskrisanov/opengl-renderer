#pragma once

#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include "utils.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"

namespace render
{
class Shader
{
  public:
    Shader(std::string name, std::vector<std::string> uniforms = {});
    void select() const;

    template <typename T>
    void setUniform(std::string name, T value) const
    {
#ifdef ENABLE_DEBUG_LOGGING
        if (!this->uniformLocations.contains(name)) [[unlikely]]
        {
            DEBUG_LOG("warning: attempted to set uniform " << name << " which does not exist on shader " << this->name << ". Uniform names must be specified in the Shader constructor.");
            return;
        }
#endif

        const int location = this->uniformLocations.at(name);
        const auto valuePointer = glm::value_ptr(value);

        static_assert(std::is_same<T, glm::mat4>::value || std::is_same<T, glm::vec3>::value || std::is_same<T, glm::vec2>::value, "Invalid shader uniform type");

        if constexpr (std::is_same<T, glm::mat4>::value)
        {
            glUniformMatrix4fv(location, 1, false, valuePointer);
        }
        else if constexpr (std::is_same<T, glm::vec3>::value)
        {
            glUniform3fv(location, 1, false, valuePointer);
        }
        else if constexpr (std::is_same<T, glm::vec2>::value)
        {
            glUniform2fv(location, 1, false, valuePointer);
        }
        else
        {
            DEBUG_LOG("Invalid shader uniform type");
        }
    }

    unsigned int id;
    const std::string name;

  private:
    std::map<std::string, int> uniformLocations;
    [[nodiscard]] unsigned int loadAndCompileShader(std::string sourcePath) const;
    void createShaderProgram(std::vector<unsigned int> shaders);
};
} // namespace render