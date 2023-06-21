#include "defs.hpp"

using std::string, std::ifstream, std::vector;

namespace render
{

Shader::Shader(std::string name)
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

    if (shaders.empty())
    {
        DEBUG_LOG("Shader loading failed: cannot find files for " << name);
        return;
    }

    this->createShaderProgram(shaders);
}

unsigned int Shader::loadAndCompileShader(std::string sourcePath)
{
    DEBUG_LOG("Loading shader: " << sourcePath);

    int shaderType = sourcePath.ends_with(".vert") ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

    ifstream sourceFile{sourcePath};
    string currentLine;
    string shaderSource;

    while (getline(sourceFile, currentLine))
    {
        currentLine += "\n";
        shaderSource += currentLine;
    }

    sourceFile.close();

    auto shaderSourceCString = shaderSource.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCString, nullptr);
    glCompileShader(shader);

    int success;
    char errorMessage[4096]; // TODO: Variable length error message
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 4096, nullptr, errorMessage);
        DEBUG_LOG("Shader compilation failed: " << errorMessage);
        // TODO: Proper error handling
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