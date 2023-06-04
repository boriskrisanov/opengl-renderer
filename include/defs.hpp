#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <format>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <memory>
#include <optional>
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

class Cube
{
  private:
    // clang-format off
    static constexpr float vertexes[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    // clang-format on

    unsigned int shaderId;
    unsigned int textureId;
    unsigned int vertexBuffer;
    unsigned int vertexArray;

  public:
    Cube(glm::vec3 position, glm::vec3 rotation, unsigned int shaderId);
    glm::vec3 position;
    glm::vec3 rotation;
    void render() const;
};

class Camera
{
  public:
    Camera(GLFWwindow *window, glm::vec2 windowSize, unsigned int shaderProgram, float speed);
    Camera() {}
    glm::vec3 position = glm::vec3(0, 0, 0);
    static constexpr float fov = 45;
    void update();

  private:
    void updateMatrixUniforms();
    void respondToKeyboardInput();
    void respondToMouseInput();
    glm::mat4 projectionMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 front;
    unsigned int shaderProgram;
    float speed;
    float pitch = 0;
    float yaw = -90;
    glm::vec2 lastMousePosition = glm::vec2(0, 0);
    glm::vec2 mouseOffset = glm::vec2(0, 0);
    GLFWwindow *window;
};

GLFWwindow *initAndCreateWindow();
void drawFrame();
void loadShaderFromFile(std::string sourcePath, ShaderType type);
unsigned int createShaderProgram();
void setWireframeDrawEnabled(bool enabled);
void initCamera(unsigned int shaderProgram);
void setVsyncEnabled(bool enabled);
void initScene(unsigned int shaderId);
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
    E = GLFW_KEY_E,
    ESCAPE = GLFW_KEY_ESCAPE
};

[[nodiscard]] bool isKeyDown(GLFWwindow *window, Key key);
[[nodiscard]] glm::vec2 getMousePosition(GLFWwindow *window);
} // namespace input