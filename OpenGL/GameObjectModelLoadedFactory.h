#pragma once

#include "GameObject.h"
#include "ModelLoader.h"
#include <vector>
#include <string>


class GameObjectModelLoadedFactory
{
public:
	GameObjectModelLoadedFactory(std::vector<std::string> paths, Shader *shader);
	GameObjectModelLoadedFactory(std::string path, glm::mat4 trans, Shader *shader);
	GameObjectModelLoadedFactory(std::string path, Shader *shader);
	~GameObjectModelLoadedFactory();

	GameObject* load() {
		modelloader->loadModel(paths[paths.size()-1]);
		paths.pop_back();
		GameObject* obj = new GameObject(modelloader->getMeshes(), shader);
		obj->setTransform(trans);
		return obj;
	}
	GameObject* load(std::string path, glm::mat4 trans, Shader *shader) {
		modelloader->loadModel(path);
		paths.pop_back();
		GameObject* obj = new GameObject(modelloader->getMeshes(), shader);
		obj->setTransform(trans);
		return obj;
	}

	std::vector<GameObject*> loadAll() {
		std::vector<GameObject*> loaded;
		for (int i = 0; i < paths.size(); i++){
			modelloader->loadModel(paths[paths.size() - 1 - i]);
			loaded.push_back(new GameObject(modelloader->getMeshes(), shader));
		}
		std::cout << loaded.size();
		return loaded;
	}

private:
	std::vector<std::string> paths;
	Shader *shader;
	glm::mat4 trans;
	ModelLoader *modelloader;
};

inline GameObjectModelLoadedFactory::GameObjectModelLoadedFactory(std::vector<std::string> paths, Shader *shader)
{
	this->paths = paths;
	this->modelloader = new ModelLoader();
	this->shader = shader;
}

inline GameObjectModelLoadedFactory::GameObjectModelLoadedFactory(std::string path, glm::mat4 trans, Shader *shader) {
	this->paths = std::vector<std::string>{ path };
	this->shader = shader;
	this->trans = trans;
}

inline GameObjectModelLoadedFactory::GameObjectModelLoadedFactory(std::string path, Shader *shader)
{
	this->paths = std::vector<std::string>{ path };
	this->trans = glm::mat4(0);
	this->shader = shader;
}

GameObjectModelLoadedFactory::~GameObjectModelLoadedFactory()
{
}

