#include "render.hpp"
#include "utils.hpp"
#include <GL/glew.h>
#include <filesystem>


using std::string, std::ifstream, std::vector;

namespace render
{

Shader::Shader(std::string name, vector<string> uniforms) : name{name}
{
    DEBUG_LOG("Looking for files for shader " << name);
    std::vector<unsigned int> shaders;

    for (auto fileName : std::filesystem::directory_iterator("assets/shaders/"))
    {
        const std::string filePath = fileName.path().string();

        if (filePath.ends_with(name + ".vert") || filePath.ends_with(name + ".frag"))
        {
            unsigned int shader = this->loadAndCompileShader(fileName.path().string());
            shaders.push_back(shader);
        }
    }

    if (shaders.empty()) [[unlikely]]
    {
        DEBUG_LOG("Shader loading failed: cannot find files for " << name);
        return;
    }

    this->createShaderProgram(shaders);

    for (std::string uniform : uniforms)
    {
        const int location = glGetUniformLocation(this->id, uniform.c_str());
        this->uniformLocations[uniform] = location;
    }
}

unsigned int Shader::loadAndCompileShader(std::string sourcePath) const
{
    DEBUG_LOG("Loading shader: " << sourcePath);

    const int shaderType = sourcePath.ends_with(".vert") ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

    const string shaderSource = utils::loadFile(sourcePath);

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
        DEBUG_LOG("Failed to compile shader " << name << ": " << errorMessage);
        exit(1);
    }

    return shader;
}

void Shader::createShaderProgram(std::vector<unsigned int> shaders)
{
    this->id = glCreateProgram();

    for (unsigned int shader : shaders)
    {
        glAttachShader(this->id, shader);
    }

    glLinkProgram(this->id);

    int success;
    char errorMessage[4096];
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->id, 512, NULL, errorMessage);
        DEBUG_LOG("Shader linking failed: " << errorMessage);
        return;
    }
}

void Shader::select() const
{
    glUseProgram(this->id);
}
} // namespace render