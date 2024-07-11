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
    camera->addComponent(new CameraComponent{});
    registry.addGameObject(camera);

    //    GameObject triangle;
    //    vector<Vertex> vertexes = {
    //        {{-0.5, -0.5, 0}},
    //        {{0.5, -0.5, 0}},
    //        {{0, 0.5, 0}}
    //    };
    /*    auto mesh = new MeshComponent{
            *(new Mesh{vertexes}),
            shader
        };
        triangle.addComponent(mesh);
        registry.addGameObject(triangle);*/

    while (!renderer.isWindowClosed())
    {
        registry.update();
    }
}
