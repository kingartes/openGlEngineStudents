#include "vector"
#include "../shaders/Shader.h"
#include "../includes/glm/vec3.hpp"
#include "../includes/glm/vec4.hpp"
#include "../includes/glm/matrix.hpp"

struct color { float r, g, b; };
struct text { glm::vec2 t[4]; };

class figure
{
public:
	figure() {};
	~figure() {};

	// init buffers in memory before loop while
	void setUpBuffers();

	// use it in loop while
	void useBuffers();
	void setTexure(unsigned int);

	// to clean memory
	void deleteBuffers();

protected:
	// buffers
	unsigned int VAO, VBO, EBO;
	// if need
	bool useEBO;
	// files names to use shaders
	const char* vs;
	const char* vp;
	
	std::vector<float> vertex;
	std::vector<unsigned int> indices;
};