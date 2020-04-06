#pragma once
#include "GameObject.h"

class ParallelogramLoader
{
public:
	ParallelogramLoader(vector<Mesh> meshes, Shader* shader)
	{ 
		this->meshes = meshes;
		parallelogram = new GameObject(meshes, shader);
	}
	ParallelogramLoader(Shader* shader) { makeCube(shader); }
	~ParallelogramLoader() { delete parallelogram; }
	GameObject* getModel() const { return parallelogram; };

private:
	vector<Mesh> meshes;
	GameObject* parallelogram;
	void makeCube(Shader* shader)
	{
		vector<Vertex> vertex =
		{
			Vertex{glm::vec3(1, 1, -1), glm::vec3(0, 1, 0), glm::vec2(0.625, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0), glm::vec2(0.875, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, 1), glm::vec3(0, 1, 0), glm::vec2(0.875, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), glm::vec2(0.625, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1), glm::vec3(0, 0, 1), glm::vec2(0.375, 0.25), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), glm::vec2(0.625, 0.25), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, 1, 1), glm::vec3(0, 0, 1), glm::vec2(0.625, 0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1), glm::vec2(0.375, 0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(-1, 0, 0), glm::vec2(0.375, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, 1), glm::vec3(-1, 0, 0), glm::vec2(0.625, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(-1, 0, 0), glm::vec2(0.625, 0.75), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, -1, -1), glm::vec3(-1, 0, 0), glm::vec2(0.375, 0.75), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, -1, -1), glm::vec3(0, -1, 0), glm::vec2(0.125, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, -1, 0), glm::vec2(0.375, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1), glm::vec3(0, -1, 0), glm::vec2(0.375, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, -1, 0), glm::vec2(0.125, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(1, 0, 0), glm::vec2(0.375, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, -1), glm::vec3(1, 0, 0), glm::vec2(0.625, 0.5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1), glm::vec3(1, 0, 0), glm::vec2(0.625, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1), glm::vec3(1, 0, 0), glm::vec2(0.375, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, -1, -1), glm::vec3(0, 0, -1), glm::vec2(0.375, 0.75), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 0, -1), glm::vec2(0.625, 0.75), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, 1, -1), glm::vec3(0, 0, -1), glm::vec2(0.625, 0.5), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, 0, -1), glm::vec2(0.375, 0.5), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)}
		};
		vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
		meshes = { Mesh(vertex, indices, vector<Texture>{}) };
		parallelogram = new GameObject( meshes, shader );
	}
};