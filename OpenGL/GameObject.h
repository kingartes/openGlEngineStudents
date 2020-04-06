#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <../mesh.h>
#include <../shaders/shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <glm/glm.hpp>


using namespace std;

//unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class GameObject
{
public:
    GameObject();
    GameObject(vector<Mesh> meshes) : meshes(meshes) {}
    GameObject(vector<Mesh> meshes, Shader *shader) : meshes(meshes), shader(shader) {}
    void setShader(Shader *shader) { this->shader = shader; }
    // draws the model, and thus all its meshes
    void Draw(Shader *shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].setTransform(trans);
            meshes[i].Draw(shader);
        }
    }
    void Draw() { Draw(this->shader); }

    void setTransform(glm::mat4 trans) { this->trans = trans; }

protected:
    /*  Model Data */
    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    Shader* shader;
    glm::mat4 trans = glm::mat4(1.0f);
};

#endif