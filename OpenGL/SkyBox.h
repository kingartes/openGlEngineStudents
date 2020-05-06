#include <vector>
#include <string>
#include "shaders/Shader.h"
#include "GameObject.h"
#include "ParallelogramLoader.h"

#pragma once
unsigned int loadCubemap(vector<std::string> faces);
class SkyBox
{
public:
	SkyBox();
	SkyBox(std::vector<std::string> faces) : faces(faces) {}
	SkyBox(std::vector<std::string> faces, Shader shader) : faces(faces), shader(shader) {}

	GameObject* create() {
        Texture t;
        t.type = "texture_skybox";
        t.id = loadCubemap(faces);
		/*
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

        Mesh mesh(vertices, indices, vector<Texture>{t});*/
        ParallelogramLoader loader(&shader, vector<Texture>{t});
        return loader.getModel();//new GameObject(vector<Mesh>{mesh});
	}
private:
	std::vector<std::string> faces;
	Shader shader;
};

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::cout << faces[i] << std::endl;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}