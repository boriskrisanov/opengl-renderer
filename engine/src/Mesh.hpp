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
    const string source;
    vector<Vertex> vertexes;
    size_t vertexCount; // TODO: vertexes can be modified without changing vertexCount
    explicit Mesh(string source);
    explicit Mesh(const vector<Vertex>& vertexes);
  private:
    vector<Vector3<>> objVertexes;
    vector<Vector3<>> objNormals;
    vector<Vector2<>> objTextureCoordinates;
};