#include "triangle.hpp"
#include <glad/glad.h>

DrawTriangles::DrawTriangles() { vertex_and_colors = {}; }

DrawTriangles::DrawTriangles(triangle vertex, color color)
{
	vertex_and_colors = {};
	add(vertex, color);
}

DrawTriangles::~DrawTriangles()
{
	deleteBuffers();
}

void DrawTriangles::add(triangle vertex, color color)
{
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[0].x, vertex.points[0].y, vertex.points[0].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[1].x, vertex.points[1].y, vertex.points[1].z, color.r, color.g, color.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { vertex.points[2].x, vertex.points[2].y, vertex.points[2].z, color.r, color.g, color.b });
}

void DrawTriangles::setUpBuffers()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex_and_colors.size() * sizeof(float), vertex_and_colors.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attributete
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
}

void DrawTriangles::useBuffers()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertex_and_colors.size());
}

void DrawTriangles::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
