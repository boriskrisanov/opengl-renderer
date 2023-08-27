#pragma once

#include "shader.hpp"
#include "GLFW/glfw3.h"
#include "context.hpp"
#include <memory>

namespace render
{
[[nodiscard]] RenderContext initAndCreateWindow(glm::vec2 windowSize, std::function<void()> onStart, std::function<void(float deltaTime)> onUpdate);
void drawFrame(render::Shader shader);
void setWireframeDrawEnabled(bool enabled);
void setVsyncEnabled(bool enabled);
void runMainLoop(RenderContext context);

// Internal, should only be called from the render namespace
// TODO: Find a better way to do this without creating this function in the header
void _addGameObject(std::shared_ptr<GameObject> gameObject);

// Instantiates a GameObject and adds it to the render context
// TODO: Forward arguments to T constructor
template <typename T> requires std::is_base_of<GameObject, T>::value
void addGameObject()
{
		// Creating a template is better than passing a shared_ptr directly because this way the engine can manage the creation and destruction of GameObjects
		// (API consumers don't have to call new or make_shared)
		
    std::shared_ptr<T> gameObject = std::make_shared<T>();
		gameObject->onStart();
		_addGameObject(gameObject);
}
} // namespace render