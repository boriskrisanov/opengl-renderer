#include "Mesh.hpp"
#include "utils.hpp"

using std::string;
using std::vector;

Mesh::Mesh(string source)
    : source{source}
{
    DEBUG_LOG("Loading OBJ mesh " + source);

    const string modelSource = loadFile(source);

    for (string line : splitString(modelSource, "\n"))
    {
        const vector<string> splitLine = splitString(line, " ");
        const string firstToken = splitLine[0];

        if (firstToken == "v")
        {
            // Vertex
            const double x = std::stod(splitLine[1]);
            const double y = std::stod(splitLine[2]);
            const double z = std::stod(splitLine[3]);
            this->objVertexes.push_back({x, y, z});
        }
        else if (firstToken == "vn")
        {
            // Normal
            const double x = std::stod(splitLine[1]);
            const double y = std::stod(splitLine[2]);
            const double z = std::stod(splitLine[3]);
            this->objNormals.push_back({x, y, z});
        }
        else if (firstToken == "vt")
        {
            // Texture coordinate
            const double x = std::stod(splitLine[1]);
            const double y = std::stod(splitLine[2]);
            this->objTextureCoordinates.push_back({x, y});
        }
        else if (firstToken == "f")
        {
            // Face
            // vertex/textureCoordinate/normal

            vector<string> faceVertexDefinitions{splitLine};
            faceVertexDefinitions.erase(faceVertexDefinitions.begin());

            if (faceVertexDefinitions.size() != 3) [[unlikely]]
            {
                DEBUG_LOG("OBJ loading failed: mesh " + source + " contains non triangular faces. OBJ file must be exported with triangulation enabled.");
                return;
            }

            for (string vertexDefinition : faceVertexDefinitions)
            {
                const vector<string> splitDefinition = splitString(vertexDefinition, "/");

                // Subtract 1 from each index because OBJ indexes start at 1
                const long vertexIndex = std::stol(splitDefinition[0]) - 1;
                const long textureCoordinateIndex = splitDefinition[1].empty() ? -1 : std::stol(splitDefinition[1]) - 1;
                const long normalIndex = std::stol(splitDefinition[2]) - 1;

                vertexes.push_back(Vertex{
                    .position = this->objVertexes[vertexIndex],
                    .normal = this->objNormals[normalIndex],
                    // TODO: Improve handling of undefined texture coordinates
                    .textureCoordinate = textureCoordinateIndex == -1 ? Vector2{0.0, 0.0} : this->objTextureCoordinates[textureCoordinateIndex],
                });
            }
        }
    }

    this->vertexCount = this->vertexes.size();
    DEBUG_LOG("Loaded OBJ mesh " + source + ", vertex count: " + std::to_string(this->vertexCount));
}

Mesh::Mesh(const vector<Vertex> &vertexes)
    : vertexes{vertexes}, vertexCount{(unsigned int)vertexes.size()}
{
}
