#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG_LOG(message) std::cout << "[" << std::chrono::system_clock::now() << "][" << __func__ << "] " << message << "\n"

namespace utils
{
[[nodiscard]] std::string loadFile(std::string path);
[[nodiscard]] std::vector<std::string> splitString(std::string str, std::string delimiter);

template <typename T>
[[nodiscard]] unsigned long long sizeOfVectorInBytes(std::vector<T> vector)
{
    return vector.size() * sizeof(T);
}

template <typename T, size_t S>
void pushBackArrayToVector(std::vector<T> &vector, std::array<T, S> array)
{
    // vector.reserve(vector.size() + array.size());

    for (size_t i = 0; i < array.size(); i++)
    {
        vector.push_back(array[i]);
    }
}
} // namespace utils