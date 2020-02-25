#include "figure.hpp"

struct triangle { 
	glm::vec4 points[3]; 
};

class Triangle : figure
{
public:
	Triangle();
	Triangle(triangle v);
	~Triangle();

	void setUpBuffers();
	void useBuffers();
	void deleteBuffers();
	void add(triangle v);
private:
	unsigned int VAO, VBO;
	std::vector<float> vertex;
	
};