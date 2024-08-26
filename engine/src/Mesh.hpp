#pragma once

#include "utils.hpp"
#include "math.hpp"

struct Vertex
{
    Vector3<> position;
    Vector3<> normal;
    Vector2<> textureCoordinate;
};

class Mesh
{
  public:
    const std::string source;
    std::vector<Vertex> vertexes;
    size_t vertexCount; // TODO: vertexes can be modified without changing vertexCount
    explicit Mesh(std::string source);
    explicit Mesh(const std::vector<Vertex>& vertexes);
  private:
    std::vector<Vector3<>> objVertexes;
    std::vector<Vector3<>> objNormals;
    std::vector<Vector2<>> objTextureCoordinates;
};