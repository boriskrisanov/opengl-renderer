#include "utils.hpp"
#include <fstream>
#include <string>

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

std::vector<std::string> splitString(std::string str, std::string delimiter)
{
    std::vector<std::string> result;

    int pos = 0;
    std::string token;
    while ((unsigned long long)(pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);

    return result;
}
} // namespace utils