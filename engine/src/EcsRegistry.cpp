#include "EcsRegistry.hpp"

EcsRegistry::EcsRegistry(Scene &scene)
    : scene{scene}
{
}

void EcsRegistry::addSystem(const std::function<void(EcsRegistry &ecsRegistry)> &updateHandler)
{
    systemHandlers.push_back(updateHandler);
}

void EcsRegistry::update()
{
    for (const auto &handler : systemHandlers)
    {
        handler(*this);
    }
}

std::vector<GameObject *> EcsRegistry::getGameObjects() const
{
    return gameObjects;
}

void EcsRegistry::addGameObject(GameObject *gameObject)
{
    // TODO: Memory management
    gameObjects.push_back(gameObject);
}

Scene &EcsRegistry::getScene() const
{
    return scene;
}
