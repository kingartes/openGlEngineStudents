#pragma once
#include "GameObject.h"
#include "ModelLoader.h"
class Square
{
public:
	Square(Texture t) {
		textures.push_back(t);
	}
	Square(string texture) {
		Texture t;
		string directory = texture.substr(0, texture.find_last_of('/'));
		string name = texture.substr(texture.find_last_of('/'));
		t.id = TextureFromFile(name.c_str(), directory);
		t.type = "texture_diffuse";
		this->textures.push_back(t);
		makeSquare();
	}
	GameObject* getSquare() {
		return square;
	}

private:
	GameObject* square;
	vector<Texture> textures;
	void makeSquare() {
		vector<Vertex> vertices{
			Vertex{glm::vec3(-1.0, -1.0,  1.0)},
			Vertex{glm::vec3(1.0, -1.0,  1.0)},
			Vertex{glm::vec3(1.0,  1.0,  1.0)},
			Vertex{glm::vec3(-1.0,  1.0,  1.0)},
		};
		vector<unsigned int> indices{
			0, 1, 2,
			2, 3, 0
		};

		Mesh m(vertices, indices, this->textures);
		square = new GameObject(vector<Mesh>{m});
	}
};

