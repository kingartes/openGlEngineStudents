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
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(0, 1, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0),  glm::vec2(0.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(0, 1, 0),  glm::vec2(1.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(0, 1, 0),  glm::vec2(1.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},

			Vertex{glm::vec3(1, -1, 1),  glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},

			Vertex{glm::vec3(-1, -1, 1), glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, -1, -1),glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},

			Vertex{glm::vec3(-1, -1, -1),glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1),  glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},

			Vertex{glm::vec3(1, -1, -1), glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1),  glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},

			Vertex{glm::vec3(-1, -1, -1),glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)}
		};
		vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
		vector<Texture> textures;
		//for (int i = 0; i < 10; i++) {ó
			Texture t;
			t.id = TextureFromFile((std::string("3.png")).c_str(), "resources/");
			
			t.type = "texture_diffuse";
			textures.push_back(t);
		//
		meshes = { Mesh(vertex, indices, textures) };
		parallelogram = new GameObject( meshes, shader );
	}
	/*
	meshes =
		{
			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(0, 1, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 1, 0),  glm::vec2(0.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(0, 1, 0),  glm::vec2(1.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(0, 1, 0),  glm::vec2(1.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t1}),

			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(1, -1, 1),  glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, 0, 1),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t}),

			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, 1),  glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)},
			Vertex{glm::vec3(-1, -1, -1),glm::vec3(-1, 0, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t}),

			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(-1, -1, -1),glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1),  glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(-1, -1, 1), glm::vec3(0, -1, 0), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t}),

			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(1, -1, -1), glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, 1, 1),   glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)},
			Vertex{glm::vec3(1, -1, 1),  glm::vec3(1, 0, 0),  glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t}),

			Mesh(
			vector<Vertex>{
			Vertex{glm::vec3(-1, -1, -1),glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(-1, 1, -1), glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, 1, -1),  glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)},
			Vertex{glm::vec3(1, -1, -1), glm::vec3(0, 0, -1), glm::vec2(0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)}
			}, vector<unsigned int>{0, 1, 2, 0, 2, 3}, vector<Texture>{t}),
		};*/
};
