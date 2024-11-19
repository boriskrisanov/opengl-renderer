#include "EcsRegistry.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Texture.hpp"
#include "ui.hpp"
#include "components/CameraComponent.hpp"
#include "components/MaterialComponent.hpp"
#include "components/MeshComponent.hpp"
#include "physics/AABB.hpp"
#include "systems/systems.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>


int main()
{
    Renderer renderer{{1920, 1080}};

    renderer.input.setCursorEnabled(false);

    ui::init(renderer.window);

    Scene scene{renderer};

    EcsRegistry& registry = scene.getEcsRegistry();

    registry.addSystem(updateRenderSystem);
    registry.addSystem(ui::updateUISystem);
    registry.addSystem(updateEndRenderSystem);
    registry.addSystem(updateCameraMovementSystem);

    const auto cube = new GameObject{};
    cube->addComponent(new MeshComponent{*(new Mesh{"assets/cube.obj"}), *renderer.shader});
    registry.addGameObject(cube);

    std::vector<Vector3<>> positions;

    for (const auto v : cube->getComponent<MeshComponent>()->mesh.vertexes)
    {
        positions.push_back(v.position);
    }

    const AABB collider{positions};

    DEBUG_LOG(collider.intersects({0, 0, -3}, {0, 0, 1}) ? "true" : "false");

    const auto camera = new GameObject{};
    camera->addComponent(new CameraComponent{renderer.getWindowSize()});
    registry.addGameObject(camera);

    // TODO: Asset loading / cache
    const auto defaultTexture = Texture{"assets/textures/uv_grid_256.jpg"};
    const auto materialComponent = new MaterialComponent{defaultTexture};
    cube->addComponent(materialComponent);

    while (!renderer.isWindowClosed())
    {
        scene.update();
        ui::update();
        ui::endUpdate();
    }

    ui::shutdown();
}
