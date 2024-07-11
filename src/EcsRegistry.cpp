#include "EcsRegistry.hpp"

void EcsRegistry::addSystem(const std::function<void(const EcsRegistry &)>& updateHandler)
{
    systemHandlers.push_back(updateHandler);
}

void EcsRegistry::update()
{
    for (const auto &handler : systemHandlers) {
        handler(*this);
    }
}

vector<GameObject*> EcsRegistry::getGameObjects() const
{
    return gameObjects;
}
void EcsRegistry::addGameObject(GameObject* gameObject)
{
    // TODO: Memory management
    gameObjects.push_back(gameObject);
}
