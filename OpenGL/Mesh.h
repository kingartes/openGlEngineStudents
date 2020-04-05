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
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures), transform(glm::mat4(1.0f)) { setupMesh(); }
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, glm::mat4 trans) : vertices(vertices), indices(indices), textures(textures), transform(trans) { setupMesh(); }
    void setTransform(glm::mat4 trans) { transform = trans; }

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