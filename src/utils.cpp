#include "defs.hpp"

namespace utils
{
std::string loadFile(std::string path)
{
    // TODO: Error handling
		DEBUG_LOG("Loading file " << path);
    std::ifstream sourceFile{path};
    std::string currentLine;
    std::string sourceString;

    while (std::getline(sourceFile, currentLine))
    {
        currentLine += "\n";
        sourceString += currentLine;
    }

    sourceFile.close();

    return sourceString;
}
} // namespace utils