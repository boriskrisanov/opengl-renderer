#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
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
    static constexpr float triangleVertices[] = {
      -0.5, -0.5, 0.5,     0, 1, 0,    // 0
      0.5, -0.5, 0.5,      0, 0, 1,    // 1
      -0.5, 0.5, 0.5,      0, 1, 0,    // 2
      0.5, 0.5, 0.5,       0, 0, 1,    // 3
      -0.5, -0.5, -0.5,    0, 1, 0,    // 4
      0.5, -0.5, -0.5,     0, 0, 1,    // 5
      -0.5, 0.5, -0.5,     0, 1, 0,    // 6
      0.5, 0.5, -0.5 ,     0, 0, 1     // 7
    };
    static constexpr unsigned int indexes[] = {
      0, 1, 3, 0, 2, 3,
      5, 1, 3, 5, 7, 3,
      5, 4, 6, 5, 7, 6,
      4, 6, 2, 4, 0, 2,
      0, 4, 1, 5, 4, 1,
      2, 6, 3, 7, 6, 3
    };
    // clang-format on

    unsigned int shaderId;

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
    E = GLFW_KEY_E
};

bool isKeyDown(GLFWwindow *window, Key key);
glm::vec2 getMousePosition(GLFWwindow *window);
} // namespace input