#include "Scene.hpp"

Scene::Scene(Renderer &renderer)
    : renderer{renderer}
{
}

void Scene::update()
{
    ecsRegistry->update();
}

EcsRegistry &Scene::getEcsRegistry() const
{
    return *ecsRegistry;
}

Renderer &Scene::getRenderer() const
{
    return renderer;
}
