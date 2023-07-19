#include "ui.hpp"
#include "input.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>


namespace ui
{

std::string openGlVersion;
std::string rendererInfo;

bool isWireframeDrawEnabled = false;

void init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    openGlVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    rendererInfo = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
}

void update(GLFWwindow *window, bool &isCursorEnabled, double &secondsUntilNextCursorStateUpdate, float SECONDS_BETWEEN_CURSOR_STATE_UPDATES, float frameTimeInMilliseconds, std::shared_ptr<const render::Camera> camera, const std::function<void()> &regenerateTerrainClicked)
{
    // TODO: Increase font size
    if (input::isKeyDown(window, input::ESCAPE) && secondsUntilNextCursorStateUpdate <= 0) [[unlikely]]
    {
        // Toggle cursor state
        isCursorEnabled = !isCursorEnabled;
        secondsUntilNextCursorStateUpdate = SECONDS_BETWEEN_CURSOR_STATE_UPDATES;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: FPS counter
    auto cameraPosition = camera->position;
    ImGui::Text("%s", std::format("Camera position: {}, {}, {} ", cameraPosition.x, cameraPosition.y, cameraPosition.z).c_str());
    ImGui::Text("%s", std::format("Frame time: {}ms", frameTimeInMilliseconds).c_str());
    ImGui::Text("%s", std::format("OpenGL version: {}", openGlVersion).c_str());
    ImGui::Text("%s", std::format("Renderer: {}", rendererInfo).c_str());

    if (ImGui::Button("Toggle wireframe"))
    {
        render::setWireframeDrawEnabled(!isWireframeDrawEnabled);
    }

    ImGui::Begin("Terrain");

    if (ImGui::Button("Regenerate terrain"))
    {
        regenerateTerrainClicked();
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace ui