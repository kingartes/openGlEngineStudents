#include "vector"
#include "../shaders/Shader.h"
#include "../includes/glm/vec3.hpp"
#include "../includes/glm/vec4.hpp"
#include "../includes/glm/matrix.hpp"

/*
Main class figure that helps create another figures classes
Notice: 
	to see example use square.hpp file
*/

// helps for constructors
struct color { float r, g, b; };
struct text { glm::vec2 t[4]; };

class figure
{
public:
	figure() {};
	~figure() {};

	// use it before loop while
	// init buffers in memory
	void setUpBuffers();

	// use it in loop while
	// set up buffers VAO, VBO and maybe EBO if you need this
	void useBuffers();

	// to clean memory
	void deleteBuffers();

	// set img textures for png, jpeg and anothers formats
	void setTexure(unsigned int texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, vertex.size(), GL_UNSIGNED_INT, 0);
	}

protected:
	// buffers
	unsigned int VAO, VBO, EBO;
	// if you need to change
	bool useEBO;
	// files names to use shaders
	const char* vs;
	const char* vp;
	Shader shader;
	// main vector that has figure position, color, and texture position
	std::vector<float> vertex;
	// use this with EBO
	std::vector<unsigned int> indices;
};