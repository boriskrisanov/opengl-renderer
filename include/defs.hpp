#pragma once

#include "PerlinNoise.hpp"
#include "defs.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <format>
#include <fstream>
#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <optional>
#include <random>
#include <stb_image.h>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#define DEBUG_LOG(message) std::cout << "[" << std::chrono::system_clock::now() << "][" << __func__ << "] " << message << "\n"

namespace world
{
struct Chunk;
}

namespace render
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinate;
};

class ObjModel
{
  public:
    ObjModel(std::string path);
    std::vector<Vertex> vertexes;

  private:
    std::vector<glm::vec3> objVertexes;
    std::vector<glm::vec3> objNormals;
    std::vector<glm::vec2> objTextureCoordinates;
};

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

        int location = location = this->uniformLocations.at(name);
        auto valuePointer = glm::value_ptr(value);

        if constexpr (std::is_same<T, glm::mat4>::value)
        {
            glUniformMatrix4fv(location, 1, false, valuePointer);
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
    unsigned int loadAndCompileShader(std::string sourcePath) const;
    void createShaderProgram(std::vector<unsigned int> shaders);
};

class Texture
{
  public:
    void select() const;
    Texture(std::string path);

  private:
    unsigned int id;
};

namespace assetLoader
{
void loadAssets();
enum class TextureName
{
    CONTAINER
};
enum class ModelName
{
    CUBE,
    SPHERE
};
const render::Texture *getTexture(TextureName name);
const render::ObjModel *getModel(ModelName name);
} // namespace assetLoader

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

    unsigned int vertexBuffer;
    unsigned int vertexArray;
    const Texture *texture;

  public:
    Cube(glm::vec3 position, glm::vec3 rotation, const Texture *const texture);
    glm::vec3 position;
    glm::vec3 rotation;
    void render(render::Shader shader) const;
};

class Camera
{
  public:
    Camera(GLFWwindow *window, glm::vec2 windowSize, render::Shader shader, float speed);
    glm::vec3 position = glm::vec3(0, 0, 0);
    static constexpr float fov = 80;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    void update();

  private:
    void updateMatrixUniforms();
    void respondToKeyboardInput();
    void respondToMouseInput();
    glm::vec3 target{0, 0, 0};
    glm::vec3 direction{glm::normalize(position - target)};
    glm::vec3 up{0, 1, 0};
    glm::vec3 front{0, 0, -1};
    float speed;
    float pitch = 0;
    float yaw = -90;
    glm::vec2 lastMousePosition = glm::vec2(0, 0);
    glm::vec2 mouseOffset = glm::vec2(0, 0);
    GLFWwindow *window;
    render::Shader shader;
};

class Skybox
{
  public:
    Skybox(const std::shared_ptr<const Camera> camera);
    void draw() const;

  private:
    static constexpr float vertexes[] = {
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f

    };

    render::Shader shader;
    unsigned int cubemapTextureId;
    unsigned int vertexBufferId;
    unsigned int vertexArrayId;
    const std::shared_ptr<const Camera> camera;
};

class GameObject
{
  public:
    GameObject(glm::vec3 position, glm::vec3 rotation, std::shared_ptr<ObjModel> model, const Texture *const texture);
    const std::shared_ptr<ObjModel> model;
    const Texture *const texture;
    glm::vec3 position;
    glm::vec3 rotation;
    void render(render::Shader shader) const;

  private:
    const unsigned long long numberOfVertexes;
    unsigned int vertexBuffer;
    unsigned int vertexArray;
};

GLFWwindow *initAndCreateWindow();
void drawFrame(render::Shader shader);
void setWireframeDrawEnabled(bool enabled);
void initCamera(render::Shader shader);
void setVsyncEnabled(bool enabled);
void initScene();

void drawChunk(world::Chunk chunk, render::Shader shader);

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

namespace world
{
class Block : public render::Cube
{
  public:
    glm::vec3 position;
    Block(glm::vec3 position);
};

class GrassBlock : public Block
{
};

struct Chunk
{
    glm::vec2 position;
    std::vector<std::shared_ptr<Block>> blocks;
};

[[nodiscard]] Chunk generateChunk(unsigned int seed, glm::vec2 position);
[[nodiscard]] std::vector<world::Chunk> generateTerrain(unsigned int seed, glm::vec2 worldSize);
} // namespace world

namespace utils
{
std::string loadFile(std::string path);
std::vector<std::string> splitString(std::string str, std::string delimiter);
template <typename T>
long long sizeOfVectorInBytes(std::vector<T> vector)
{
    return vector.size() * sizeof(T);
}
} // namespace utils
