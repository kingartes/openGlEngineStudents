#include "vector"
#include "../shaders/Shader.h"
#include "../includes/glm/vec3.hpp"
#include "../includes/glm/vec4.hpp"
#include "../includes/glm/matrix.hpp"

struct color { float r, g, b; };

class figure
{
public:
	figure() {};
	~figure() {};

	void setShaders();
	void setUpBuffers();
	void useBuffers();
	void deleteBuffers();
protected:
	unsigned int VAO, VBO, EBO;
	bool useEBO;
	char* vs, vp;
	std::vector<float> vertex;
	std::vector<unsigned int> indices;
};