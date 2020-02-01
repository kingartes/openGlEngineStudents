#include <vector>
#include "figures/triangle.hpp"

int InitApp(std::vector<float>);
int Rendering(std::vector<float>);

int main()
{
	using std::vector;
	using glm::vec3;
	using glm::vec4;
	triangle check = {
		vec4(-0.5, -0.5, 0.0, 1.0),
		vec4(0.5, -0.5, 0.0, 1.0),
		vec4(0.0, 0.5, 0.0, 1.0)
	};
	DrawTriangles T = DrawTriangles(check, color{ 1.0, 0.0, 0.0 });
	if (!InitApp(T.getVertexAndColors()))
		Rendering(T.getVertexAndColors());
	else
		return -1;
	return 0;
}