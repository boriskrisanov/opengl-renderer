#include "game/game.hpp"
#include "render/render.hpp"
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

	render::addGameObject({{8, 5, 8}, {0, 0, 0}, render::assetLoader::ModelName::CUBE, render::assetLoader::TextureName::UV_GRID_256});
}

void onUpdate(float deltaTime)
{
		// TODO: Make deltaTime optional in onUpdate
    (void) deltaTime;
}
} // namespace game