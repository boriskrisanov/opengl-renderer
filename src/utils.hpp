#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <optional>
#include <memory>

using std::vector, std::string, std::optional, std::unique_ptr, std::shared_ptr, std::make_shared, std::make_unique;

#define DEBUG_LOG(message) std::cout << "[" << std::chrono::system_clock::now() << "][" << __func__ << "] " << message << "\n"

[[nodiscard]] std::string loadFile(std::string path);
[[nodiscard]] std::vector<std::string> splitString(std::string str, std::string delimiter);