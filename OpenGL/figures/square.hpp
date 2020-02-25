#include "figure.hpp"
#include <glad/glad.h>

struct square
{
	glm::vec4 points[4];
};

class Square : figure
{
public:
	Square();
	Square(square t, color c);
	~Square();

	void setShaders(const char* vs, const char* ps);
	void setUpBuffers();
	void useBuffers();
	void deleteBuffers();
	
private:
	unsigned int VAO, VBO, EBO;
	const char* vs;
	const char* vp;
	void add(square t, color c);
	std::vector<unsigned int> indices;
	std::vector<float> vertex;
};
