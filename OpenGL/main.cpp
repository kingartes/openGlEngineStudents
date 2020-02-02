#include "figures/square.hpp"

int InitApp();
int Rendering(DrawTriangles& c, DrawSquare& v);

int main()
{
	using glm::vec3;
	using glm::vec4;
	triangle check1 = 
	{
		vec4(-0.5, -0.5, 0.0, 1.0),
		vec4(0.5, -0.5, 0.0, 1.0),
		vec4(0.0, 0.5, 0.0, 1.0)
	};
	square check2 =
	{
		vec4(0.5, 0.5, 0.0, 1.0),
		vec4(0.5, -0.5, 0.0, 1.0),
		vec4(-0.5, -0.5, 0.0, 1.0),
		vec4(-0.5, 0.5, 0.0, 1.0)
	};
	DrawTriangles drw = DrawTriangles(check1, color{ 1.0, 0.0, 0.0 });
	DrawSquare drs = DrawSquare(check2, color{ 0.4, 0.0, 0.0 });
	if (!InitApp()) 
	{
		drw.setUpBuffers();
		drs.setUpBuffers();
		Rendering(drw, drs);
	}
	else
		return -1;
	return 0;
}