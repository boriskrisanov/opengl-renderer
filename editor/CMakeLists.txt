cmake_minimum_required(VERSION 3.28)
project(editor VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

add_executable(editor src/main.cpp
        src/ui.cpp
        src/ui.hpp)
find_package(glm CONFIG REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/engine/src")
target_link_libraries(editor engine glm::glm)

add_compile_definitions(ENABLE_DEBUG_LOGGING)