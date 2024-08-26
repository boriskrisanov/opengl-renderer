#pragma once

#include <string>
#include <vector>

void debugLog(const std::string& function, const std::string& message);

#ifdef ENABLE_DEBUG_LOGGING
#define DEBUG_LOG(message) debugLog(__func__, message)
#else
#define DEBUG_LOG(message)
#endif
[[nodiscard]] std::string loadFile(std::string path);
[[nodiscard]] std::vector<std::string> splitString(std::string str, std::string delimiter);