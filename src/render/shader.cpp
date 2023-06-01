#include "defs.hpp"

using std::string, std::ifstream, std::vector;

namespace render {
vector<unsigned int> shaders;

void loadShaderFromFile(std::string sourcePath, ShaderType type) {
    DEBUG_LOG("Loading shader: " << sourcePath);

    ifstream sourceFile{sourcePath};
    string currentLine;
    string shaderSource;

    while (getline(sourceFile, currentLine)) {
        currentLine += "\n";
        shaderSource += currentLine;
    }

    sourceFile.close();

    auto shaderSourceCString = shaderSource.c_str();

    unsigned int shader = glCreateShader((GLenum)type);
    glShaderSource(shader, 1, &shaderSourceCString, nullptr);
    glCompileShader(shader);

    int success;
    char errorMessage[4096]; // TODO: Variable length error message
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 4096, nullptr, errorMessage);
        DEBUG_LOG("Shader compilation failed" << errorMessage);
        return;
    }

    shaders.push_back(shader);
}

unsigned int createShaderProgram() {
    unsigned int shaderProgram = glCreateProgram();

    for (unsigned int shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }

    glLinkProgram(shaderProgram);

    int success;
    char errorMessage[4096];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorMessage);
        DEBUG_LOG("Shader linking failed: " << errorMessage);
    }

    glUseProgram(shaderProgram);

    return shaderProgram;
}
} // namespace render