#include "game/game.hpp"
#include "render/gameObject.hpp"
#include "render/render.hpp"
#include "ui.hpp"
#include <imgui.h>
#include "game/cube.hpp"

namespace game
{
void terrainGenerationCallback()
{
	// TODO
}

void onStart()
{
	// ui::addWidget([] {
	// 	ImGui::Begin("Terrain");

  //   ImGui::SetWindowFontScale(2);

  //   if (ImGui::Button("Regenerate terrain"))
  //   {
	// 		terrainGenerationCallback();
  //   }
	// });

	// std::vector<world::Chunk> chunks = world::generateTerrain(1234, {1, 1});

	// render::addGameObject({{8, 5, 8}, {0, 0, 0}, render::assetLoader::ModelName::CUBE, render::assetLoader::TextureName::UV_GRID_256});

	render::addGameObject<Cube>();
}

void onUpdate(float deltaTime)
{
		// TODO: Make deltaTime optional in onUpdate
    (void) deltaTime;
}
} // namespace game