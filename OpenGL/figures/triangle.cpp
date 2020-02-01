#include "triangle.hpp"

DrawTriangles::DrawTriangles()
{
	vertex_and_colors = {};
}

DrawTriangles::DrawTriangles(triangle vertex, color color)
{
	vertex_and_colors = {};
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[0].x, vertex.points[0].y, vertex.points[0].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[1].x, vertex.points[1].y, vertex.points[1].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[2].x, vertex.points[2].y, vertex.points[2].z, color.r, color.g, color.b });

}

void DrawTriangles::add(triangle vertex, color color)
{
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[0].x, vertex.points[0].y, vertex.points[0].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[1].x, vertex.points[1].y, vertex.points[1].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[2].x, vertex.points[2].y, vertex.points[2].z, color.r, color.g, color.b });
}
