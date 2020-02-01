#include "vector"
#include "../includes/glm/vec3.hpp"
#include "../includes/glm/vec4.hpp"

struct triangle 
{
	glm::vec4 points[3];
};

struct color 
{
	float r;
	float g;
	float b;
};

class DrawTriangles
{
public:
	DrawTriangles();
	DrawTriangles(triangle v, color c);
	~DrawTriangles() {}
	void add(triangle v, color c);
	std::vector<float> getVertexAndColors() const { return vertex_and_colors; }

private:
	std::vector<float> vertex_and_colors;
};