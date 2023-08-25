#include "game/game.hpp"
#include "ui.hpp"
#include <imgui.h>


namespace game
{
void terrainGenerationCallback()
{
	DEBUG_LOG("test");
}

void onStart()
{
	ui::addWidget([] {
		ImGui::Begin("Terrain");

    ImGui::SetWindowFontScale(2);

    if (ImGui::Button("Regenerate terrain"))
    {
			terrainGenerationCallback();
    }
	});
}

void onUpdate(float deltaTime)
{
    
}
} // namespace game