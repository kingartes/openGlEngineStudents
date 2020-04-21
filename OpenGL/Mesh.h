#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <../shaders/shader.h>

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
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures) { setupMesh(); }
    // render the mesh
    void Draw(Shader* shader);

private:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    /*  Render data  */
    unsigned int VAO, VBO, EBO;
    glm::mat4 transform;

    // initializes all the buffer objects/arrays
    void setupMesh();
};