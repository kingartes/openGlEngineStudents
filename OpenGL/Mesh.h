#pragma once
#include <glad/glad.h> // holds all OpenGL type declarations

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"

#include <../shaders/shader.h>

#include <string>
#include <vector>
using std::vector;
using std::string;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    /*  Functions  */
    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    // render the mesh
    void Draw(Shader shader);
    void setTransform(glm::mat4 trans) { this->trans = trans; }

private:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    /*  Render data  */
    unsigned int VBO, EBO, VAO;
    glm::mat4 trans = glm::mat4(1.0f);

    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh();
};