#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <stb_image.h>
#include <string>
#include <thread>
#include <vector>

#define DEBUG_LOG(message) std::cout << "[" << __func__ << "] " << message << "\n"

namespace render
{
enum class ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
};

class Camera
{
  public:
    Camera(GLFWwindow *window, glm::vec2 windowSize, unsigned int shaderProgram, float speed);
    Camera() {}
    void updateMatrixUniforms();
    void respondToKeyboardInput(double deltaTime);
    void respondToMouseInput();

  private:
    glm::mat4 projectionMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 position = glm::vec3(0, 0, 0);
    unsigned int shaderProgram;
    float speed;
    float pitch = 0;
    float yaw = -90;
    glm::vec2 lastMousePosition = glm::vec2(0, 0);
    glm::vec2 mouseOffset = glm::vec2(0, 0);
    GLFWwindow *window;
};

class Texture
{
  public:
    Texture(std::string sourcePath);
    ~Texture();
    const unsigned char *textureData;
    int width;
    int height;
};

struct Vertex
{
    int positionX, positionY, positionZ;
    int textureCoordinateX, textureCoordinateY;
};

class VertexBuffer
{
  public:
    VertexBuffer(std::vector<Vertex>);
    ~VertexBuffer();
    void select();

    unsigned int id;

  private:
    std::vector<Vertex> data;
};

class Mesh
{
  public:
    Mesh(std::vector<float> vertexes);
    Mesh() {}
    ~Mesh();
    void draw();

  private:
    std::vector<float> vertexes;
    unsigned int vertexBufferId;
};

GLFWwindow *initAndCreateWindow();
void drawFrame();
void loadShaderFromFile(std::string sourcePath, ShaderType type);
unsigned int createShaderProgram();
void setWireframeDrawEnabled(bool enabled);
void initCamera(unsigned int shaderProgram);
void setVsyncEnabled(bool enabled);
} // namespace render

namespace input
{
enum Key
{
    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D,
    Q = GLFW_KEY_Q,
    E = GLFW_KEY_E
};

bool isKeyDown(GLFWwindow *window, Key key);
glm::vec2 getMousePosition(GLFWwindow *window);
} // namespace input