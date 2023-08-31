#pragma once

#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include "Scene.hpp"
#include "WindowSize.hpp"

namespace render
{
class Renderer
{
public:
	Renderer(WindowSize windowSize, std::function<void()> onStart, std::function<void(float deltaTime)> onUpdate);
	~Renderer();

	void begin();
	void exit() noexcept;
	void loadScene(std::shared_ptr<Scene> scene) noexcept;
	[[nodiscard]] double getFrameTime() const noexcept;
	[[nodiscard]] double getDeltaTime() const noexcept;

	bool vsyncEnabled = true;
	bool wireframeDrawEnabled = false;

private:
	void drawFrame();
	void updateDeltaTime() noexcept;

	GLFWwindow* window;
	double deltaTime = 0;
	double lastFrameTime = 0;
	double currentFrameTime = 0;
	glm::vec2 windowSize = { 1920, 1080 };
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Shader> shader;
	std::function<void()> onStart;
	std::function<void(float deltaTime)> onUpdate;
	double lastTime = 0;
	bool shouldExit = false;
	std::shared_ptr<Scene> currentScene;
};
} // namespace render