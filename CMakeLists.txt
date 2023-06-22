cmake_minimum_required(VERSION 3.0.0)
project(game_engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB sources CONFIGURE_DEPENDS "include/*.hpp" "src/*.cpp" "include/**/*.hpp" "src/**/*.cpp")
add_executable(game_engine ${sources})

target_link_libraries(game_engine PRIVATE glfw)
target_link_libraries(game_engine PRIVATE GLEW::GLEW)
target_link_libraries(game_engine PRIVATE imgui::imgui)

include_directories(include)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

add_compile_definitions(ENABLE_DEBUG_LOGGING)

# TODO: Delete assets directory first

add_custom_command(TARGET game_engine PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:game_engine>/assets)
