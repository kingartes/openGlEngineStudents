#pragma once
#include "GameObject.h"

class ParallelogramLoader
{

public:
	ParallelogramLoader(Shader* shader, vector<string> textures) :shader(shader)
	{ 
		parallelogram = new GameObject(meshes, shader);
		for (int i = 0; i < textures.size(); i++) {
			//vector<Texture> textures;
			//for (int i = 0; i < 10; i++) {ó
			Texture t;
			string directory = textures[i].substr(0, textures[i].find_last_of('/'));
			string name = textures[i].substr(textures[i].find_last_of('/'));
			t.id = TextureFromFile(name.c_str(), directory);
			t.type = "texture_diffuse";
			this->textures.push_back(t);
		}
		makeCube();
	}
	ParallelogramLoader(Shader* shader, vector<Texture> textures):textures(textures), shader(shader)
	{
		this->textures = textures;
		makeCube();
	}
	ParallelogramLoader(Shader* shader):shader(shader) {
		makeCube(); 
	}
	GameObject* getModel() {
		return this->parallelogram;
	}
	~ParallelogramLoader() {}
private:
	vector<Mesh> meshes;
	GameObject* parallelogram;
	vector<Texture> textures;
	Shader* shader;
	void makeCube()
	{
		std::cout << "making cube" << std::endl;
		vector<Vertex> vertices{
			Vertex{glm::vec3(-1.0, -1.0,  1.0)},
			Vertex{glm::vec3(1.0, -1.0,  1.0)},
			Vertex{glm::vec3(1.0,  1.0,  1.0)},
			Vertex{glm::vec3(-1.0,  1.0,  1.0)},

			Vertex{glm::vec3(-1.0, -1.0, -1.0)},
			Vertex{glm::vec3(1.0, -1.0, -1.0)},
			Vertex{glm::vec3(1.0,  1.0, -1.0)},
			Vertex{glm::vec3(-1.0,  1.0, -1.0)},
		};
		vector<unsigned int> indices{
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,

			6, 7, 3
		};

		Mesh m(vertices, indices, this->textures);
		parallelogram = new GameObject(vector<Mesh>{m});
	}
};