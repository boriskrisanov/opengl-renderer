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

// Returns the number of elements in the array
template <typename T>
[[nodiscard]] constexpr unsigned long sizeOfArray(const T *const array)
{
    return sizeof(*array) / sizeof(T);
}

template <typename T>
void pushBackArrayToVector(std::vector<T> &vector, const T *const array)
{
    const unsigned long sizeOfArray = utils::sizeOfArray(array);

    vector.reserve(vector.size() + sizeOfArray);

    for (int i = 0; i < sizeOfArray; i++)
    {
        vector.push_back(array[i]);
    }
}
} // namespace utils