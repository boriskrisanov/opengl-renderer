cmake_minimum_required(VERSION 3.28)
project(engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(engine
        src/Renderer.cpp
        src/Renderer.hpp
        src/math.hpp
        src/Shader.cpp
        src/Shader.hpp
        src/utils.hpp
        src/utils.cpp
        src/GameObject.hpp
        src/Component.hpp
        src/EcsRegistry.hpp
        src/EcsRegistry.cpp
        src/systems/renderSystem.cpp
        src/components/MeshComponent.hpp
        src/Mesh.cpp
        src/Mesh.hpp
        src/components/MeshComponent.cpp
        src/components/CameraComponent.cpp
        src/components/CameraComponent.hpp
        src/input.hpp
        src/input.cpp
        src/systems/cameraMovementSystem.cpp
        src/stb_impl.cpp
        src/components/MaterialComponent.hpp
        src/Texture.cpp
        src/Texture.hpp
        src/Skybox.cpp
        src/Skybox.hpp
        src/Scene.cpp
        src/Scene.hpp
        src/systems/systems.hpp
)

target_link_libraries(engine PRIVATE glfw)
target_link_libraries(engine PRIVATE GLEW::GLEW)
target_link_libraries(engine PRIVATE imgui::imgui)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/GR /W4 /external:anglebrackets /external:W0 /EHa")
endif ()

add_compile_definitions(ENABLE_DEBUG_LOGGING)