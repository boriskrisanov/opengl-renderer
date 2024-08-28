#include "Shader.hpp"
#include <GL/glew.h>
#include <filesystem>
#include <glm/ext.hpp>

using std::string, std::vector;

unsigned int loadAndCompileShader(const string &sourcePath)
{
    DEBUG_LOG("Loading shader: " + sourcePath);

    const int shaderType = sourcePath.ends_with(".vert") ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

    const string shaderSource = loadFile(sourcePath);

    auto shaderSourceCString = shaderSource.c_str();

    const unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCString, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) [[unlikely]]
    {
        int errorMessageLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorMessageLength);
        std::unique_ptr<char[]> errorMessage = std::make_unique<char[]>(errorMessageLength);

        glGetShaderInfoLog(shader, errorMessageLength, nullptr, errorMessage.get());
        DEBUG_LOG("Failed to compile shader " + sourcePath + ": " + string{errorMessage.get()});
    }

    return shader;
}

void Shader::createShaderProgram(const vector<unsigned int> &shaders)
{
    this->id = glCreateProgram();

    for (unsigned int shader : shaders)
    {
        glAttachShader(this->id, shader);
    }

    glLinkProgram(this->id);

    int success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) [[unlikely]]
    {
        int errorMessageLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &errorMessageLength);
        std::unique_ptr<char[]> errorMessage = std::make_unique<char[]>(errorMessageLength);

        glGetProgramInfoLog(this->id, errorMessageLength, nullptr, errorMessage.get());
        DEBUG_LOG("Failed to link shader " + name + ": " + string{errorMessage.get()});
        exit(1);
    }
}

Shader::Shader(const string &name, const vector<string> &uniforms)
    : name{name}
{
    std::vector<unsigned int> shaders;

    for (const auto &fileName : std::filesystem::directory_iterator("assets/shaders/"))
    {
        const std::string filePath = fileName.path().string();

        if (filePath.ends_with(name + ".vert") || filePath.ends_with(name + ".frag"))
        {
            unsigned int shader = loadAndCompileShader(fileName.path().string());
            shaders.push_back(shader);
        }
    }

    if (shaders.empty()) [[unlikely]]
    {
        DEBUG_LOG("Shader loading failed: cannot find files for " + name);
        return;
    }

    createShaderProgram(shaders);

    for (const string &uniform : uniforms)
    {
        const int location = glGetUniformLocation(this->id, uniform.c_str());

        if (location == -1)
        {
            DEBUG_LOG("warning: uniform " + uniform + " does not exist on shader " + name);
            return;
        }

        uniformLocations[uniform] = location;
    }
}

Shader::~Shader()
{
    DEBUG_LOG("Shader " + name + " destroyed");
    // TODO: Free opengl resources
}

unsigned int Shader::getId() const
{
    return id;
}

void Shader::select() const
{
    glUseProgram(id);
}
int Shader::getUniformLocation(const string &uniform) const
{
    return uniformLocations.at(uniform);
}

void Shader::setUniform(const string &uniform, glm::mat4 value) const
{
    glUniformMatrix4fv(getUniformLocation(uniform), 1, false, glm::value_ptr(value));
}

void Shader::setUniform(const string &uniform, Vector3<float> value) const
{
    glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
}
