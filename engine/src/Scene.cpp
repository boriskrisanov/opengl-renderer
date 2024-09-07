#include "Scene.hpp"

Scene::Scene(Renderer &renderer)
    : renderer{renderer}
{
}

void Scene::update()
{
    deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
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

double Scene::getDeltaTime() const
{
    return deltaTime;
}
