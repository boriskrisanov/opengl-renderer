#include "ui.hpp"
#include <functional>
#include "input.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>

namespace ui
{

	std::string openGlVersion;
	std::string rendererInfo;

	const float SECONDS_BETWEEN_COUNTER_UPDATES = 1;
	float secondsUntilNextCounterUpdate = SECONDS_BETWEEN_COUNTER_UPDATES;

	const float SECONDS_BETWEEN_CURSOR_STATE_UPDATES = 0.25;
	float secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;

	float frameTimeInMilliseconds = 0;

	std::vector<std::function<void()>> widgets;

	std::shared_ptr<const render::Camera> _camera;

	void init(GLFWwindow* window, std::shared_ptr<const render::Camera> camera)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		openGlVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		rendererInfo = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

		_camera = camera;
	}

	void update(GLFWwindow* window, bool& isWireframeDrawEnabled, bool& isCursorEnabled, float frameTimeInSeconds)
	{
		// TODO: Don't do this every frame
		glfwSetInputMode(window, GLFW_CURSOR, isCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

		secondsUntilNextCounterUpdate -= frameTimeInSeconds * 1000;
		secondsUntilNextCursorStateUpdate -= frameTimeInSeconds * 1000;

		if (secondsUntilNextCounterUpdate <= 0)
		{
			frameTimeInMilliseconds = frameTimeInSeconds * 1000;
			secondsUntilNextCounterUpdate = SECONDS_BETWEEN_COUNTER_UPDATES;
		}

		if (input::isKeyDown(window, input::Key::ESCAPE) && secondsUntilNextCursorStateUpdate <= 0) [[unlikely]]
			{
				// Toggle cursor state
				isCursorEnabled = !isCursorEnabled;
				secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;
			}

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Render");

			ImGui::SetWindowFontScale(2);

			// TODO: FPS counter
			auto cameraPosition = _camera->position;
			ImGui::Text("%s", std::format("Camera position: {}, {}, {} ", cameraPosition.x, cameraPosition.y, cameraPosition.z).c_str());
			ImGui::Text("%s", std::format("Frame time: {}ms", frameTimeInMilliseconds).c_str());
			ImGui::Text("%s", std::format("OpenGL version: {}", openGlVersion).c_str());
			ImGui::Text("%s", std::format("Renderer: {}", rendererInfo).c_str());

			if (ImGui::Button("Toggle wireframe"))
			{
				isWireframeDrawEnabled = !isWireframeDrawEnabled;
			}

			// Draw externally defined widgets
			for (std::function<void()> drawCallback : widgets)
			{
				drawCallback();
			}

			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}