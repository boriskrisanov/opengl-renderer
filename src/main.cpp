#include "Renderer.hpp"
#include "Shader.hpp"

#include "EcsRegistry.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "components/CameraComponent.hpp"
#include "components/MeshComponent.hpp"
#include "components/MaterialComponent.hpp"
#include "systems/cameraMovementSystem.hpp"
#include "systems/renderSystem.hpp"

int main()
{
    Renderer renderer{{1920, 1080}};

    Shader shader{"default", {"viewMatrix", "projectionMatrix", "transform"}};
    shader.select();

    EcsRegistry registry{renderer, shader};

    registry.addSystem(updateRenderSystem);
    registry.addSystem(updateCameraMovementSystem);

    auto cube = new GameObject{};
    cube->addComponent(new MeshComponent{*(new Mesh{"assets/cube.obj"}), shader});
    registry.addGameObject(cube);

    auto camera = new GameObject{};
    camera->addComponent(new CameraComponent{renderer.getWindowSize()});
    registry.addGameObject(camera);

    // TODO: Asset loading / cache
    auto defaultTexture = Texture{"assets/textures/uv_grid_256.jpg"};
    auto materialComponent = new MaterialComponent{defaultTexture};
    cube->addComponent(materialComponent);

    while (!renderer.isWindowClosed())
    {
        registry.update();
    }
}
