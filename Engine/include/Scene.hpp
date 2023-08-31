#pragma once

#include <vector>
#include <gameObject.hpp>
#include <skybox.hpp>

namespace render
{
	class Scene
	{
	public:
		Scene(Skybox skybox);

		void draw(std::shared_ptr<Shader> shader);

		Skybox skybox;

		template <typename T> requires std::is_base_of<GameObject, T>::value
		void addGameObject()
		{
			// Creating a template is better than passing a shared_ptr directly because this way the engine can manage the creation and destruction of GameObjects
			// (API consumers don't have to call new or make_shared)

			auto gameObject = std::make_shared<T>();
			gameObject->onStart();
			gameObjects.push_back(gameObject);
		}
		
	private:
		std::vector<std::shared_ptr<GameObject>> gameObjects = {};
	};
}