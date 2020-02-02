#include "triangle.hpp"

struct square
{
	glm::vec4 points[4];
};

class DrawSquare
{
public:
	DrawSquare();
	DrawSquare(square t, color c);
	~DrawSquare();
	void add(square v, color c);

	void setUpBuffers();
	void useBuffers();
	void deleteBuffers();

private:
	unsigned int VAO, VBO, EBO;
	unsigned int n;
	std::vector<unsigned int> indices;
	std::vector<float> vertex_and_colors;
};
