#include "utils.hpp"
#include <iostream>
#include <chrono>

void debugLog(const std::string& function, const std::string& message)
{
    std::cout << "[" << std::chrono::system_clock::now() << "][" << function << "] " << message << "\n";
}