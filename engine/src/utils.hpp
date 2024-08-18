#pragma once

#include <chrono>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using std::vector, std::string, std::optional, std::unique_ptr, std::shared_ptr, std::make_shared, std::make_unique;

#ifdef ENABLE_DEBUG_LOGGING
#define DEBUG_LOG(message) std::cout << "[" << std::chrono::system_clock::now() << "][" << __func__ << "] " << message << "\n"
#else
#define DEBUG_LOG(message)
#endif

[[nodiscard]] std::string loadFile(std::string path);
[[nodiscard]] std::vector<std::string> splitString(std::string str, std::string delimiter);