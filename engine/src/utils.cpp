#include "utils.hpp"
#include <fstream>

string loadFile(string path)
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

std::vector<string> splitString(string str, string delimiter)
{
    std::vector<string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);

    return result;
}