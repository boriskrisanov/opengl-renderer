#pragma once

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


#define DEBUG_LOG(message) std::cout << "[" << std::chrono::system_clock::now() << "][" << __func__ << "] " << message << "\n"

namespace utils
{
[[nodiscard]] std::string loadFile(std::string path);
[[nodiscard]] std::vector<std::string> splitString(std::string str, std::string delimiter);

template <typename T>
[[nodiscard]] long long sizeOfVectorInBytes(std::vector<T> vector)
{
    return vector.size() * sizeof(T);
}
} // namespace utils