#include "figure.hpp"
#include <glad/glad.h>

struct square
{
	glm::vec4 points[4];
};

class Square : public figure
{
public:
	Square();
	Square(square t, color c, text p);
	~Square();
	/*
	void setUpBuffers();
	void useBuffers();
	void deleteBuffers();
	void setTexure(unsigned int);
	*/
private:
	void add(square t, color c, text p);
};
