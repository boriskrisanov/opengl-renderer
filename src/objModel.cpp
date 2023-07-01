#include "defs.hpp"

using std::string, std::ifstream, std::vector;

namespace render
{

ObjModel::ObjModel(string path)
{
    DEBUG_LOG("Loading OBJ model " << path);

    const string modelSource = utils::loadFile(path);

    for (string line : utils::splitString(modelSource, "\n"))
    {
        const vector<string> splitLine = utils::splitString(line, " ");
        const string firstToken = splitLine[0];

        if (line.starts_with("#")) [[unlikely]]
        {
            // Comment
            continue;
        }
        else if (firstToken == "v")
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
                DEBUG_LOG("OBJ loading failed: mesh " << path << " contains non triangular faces. OBJ file must be exported with triangulation enabled.");
                return;
            }

            for (string vertexDefinition : faceVertexDefinitions)
            {
                const vector<string> splitDefinition = utils::splitString(vertexDefinition, "/");

                // Subtract 1 from each index because OBJ indexes start at 1
                const long vertexIndex = std::stol(splitDefinition[0]) - 1;
                const long textureCoordinateIndex = std::stol(splitDefinition[1]) - 1;
                const long normalIndex = std::stol(splitDefinition[2]) - 1;

                vertexes.push_back(Vertex{
                    .position = this->objVertexes[vertexIndex],
                    .normal = this->objNormals[normalIndex],
                    .textureCoordinate = this->objTextureCoordinates[textureCoordinateIndex],
                });
            }
        }
    }
}
} // namespace render