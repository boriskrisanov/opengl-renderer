#pragma once

#include "render/texture.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace render
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinate;
};

class Mesh
{
  public:
    std::vector<Vertex> vertexes;
    size_t vertexCount;
};

class ObjModel : public Mesh
{
  public:
    ObjModel(std::string path);

  private:
    std::vector<glm::vec3> objVertexes;
    std::vector<glm::vec3> objNormals;
    std::vector<glm::vec2> objTextureCoordinates;
};

struct Model
{
  Texture texture;
  Mesh mesh;
};

} // namespace render