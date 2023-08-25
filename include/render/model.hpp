#pragma once

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
} // namespace render