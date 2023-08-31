#include "Scene.hpp"

render::Scene::Scene(Skybox skybox) : skybox{skybox}
{

}

void render::Scene::draw(std::shared_ptr<Shader> shader)
{
	skybox.draw();

	shader->select();

	for (auto& gameObject : gameObjects)
	{
		gameObject->onUpdate();
		gameObject->draw(*shader);
	}
}
