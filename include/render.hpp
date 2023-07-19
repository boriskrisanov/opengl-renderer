#pragma once

#include "utils.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/ext.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

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
    CONTAINER,
    GRASS,
    DIRT,
    MISSING_TEXTURE,
    UV_GRID_256
};
enum class ModelName
{
    CUBE,
    SPHERE
};
[[nodiscard]] const render::Texture *getTexture(TextureName name);
[[nodiscard]] const render::ObjModel *getModel(ModelName name);
} // namespace assetLoader

class Camera
{
  public:
    Camera(GLFWwindow *window, glm::vec2 windowSize, render::Shader shader, float speed);
    glm::vec3 position = glm::vec3(0, 0, 0);
    static constexpr float fov = 80;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    void update(float deltaTime);

  private:
    void updateMatrixUniforms();
    void respondToKeyboardInput(float deltaTime);
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

class Scale
{
  public:
    Scale(float scale) : x{scale}, y{scale}, z{scale} {}
    Scale(glm::vec3 scale) : x{scale.x}, y{scale.y}, z{scale.z} {}
    const float x;
    const float y;
    const float z;
};

class GameObject
{
  public:
    bool isVisible = true;
    GameObject(glm::vec3 position, glm::vec3 rotation, render::assetLoader::ModelName model, render::assetLoader::TextureName texture = assetLoader::TextureName::UV_GRID_256, render::Scale scale = 1);
    const ObjModel *const model;
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

} // namespace render