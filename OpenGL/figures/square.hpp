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
private:
	void add(square t, color c, text p);
};
