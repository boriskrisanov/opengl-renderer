#include "Scene.hpp"

render::Scene::Scene(Skybox skybox) : skybox{skybox}
{

}

void render::Scene::draw(Shader shader)
{
	skybox.draw();

	for (auto& gameObject : gameObjects)
	{
		gameObject->onUpdate();
		gameObject->draw(shader);
	}
}
