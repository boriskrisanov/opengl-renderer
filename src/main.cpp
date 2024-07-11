#include "Renderer.hpp"
#include "Shader.hpp"

#include "EcsRegistry.hpp"
#include "GameObject.hpp"
#include "components/MeshComponent.hpp"
#include "components/CameraComponent.hpp"
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

    while (!renderer.isWindowClosed())
    {
        registry.update();
    }
}
