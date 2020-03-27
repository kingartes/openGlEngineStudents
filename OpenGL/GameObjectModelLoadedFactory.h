#pragma once

#include "GameObject.h"
#include "ModelLoader.h"
#include <vector>
#include <string>


class GameObjectModelLoadedFactory
{
public:
	GameObjectModelLoadedFactory(std::vector<std::string> paths);
	~GameObjectModelLoadedFactory();

	GameObject* load() {
		modelloader->loadModel(paths[paths.size()-1]);
		paths.pop_back();
		return new GameObject(modelloader->getMeshes());
	}
	std::vector<GameObject*> loadAll() {
		std::vector<GameObject*> loaded;
		for (auto it = paths.begin(); it != paths.end(); ++it) {
			modelloader->loadModel(paths[paths.size() - 1]);
			loaded.push_back(new GameObject(modelloader->getMeshes()));
		}
		std::cout << loaded.size();
		return loaded;
	}

private:
	std::vector<std::string> paths;
	ModelLoader *modelloader;
};

GameObjectModelLoadedFactory::GameObjectModelLoadedFactory(std::vector<std::string> paths)
{
	this->paths = paths;
	this->modelloader = new ModelLoader();
}

GameObjectModelLoadedFactory::~GameObjectModelLoadedFactory()
{
}

