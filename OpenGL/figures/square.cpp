#include "square.hpp"
#include <glad/glad.h>

DrawSquare::DrawSquare()
{
	vertex_and_colors = {};
	n = 0;
}

DrawSquare::DrawSquare(square v, color c)
{
	vertex_and_colors = {};
	n = 0;
	add(v, c);
}

DrawSquare::~DrawSquare()
{
	deleteBuffers();
}

void DrawSquare::add(square v, color c)
{
	vertex_and_colors.insert(vertex_and_colors.end(), { v.points[0].x, v.points[0].y, v.points[0].z, c.r, c.g, c.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { v.points[1].x, v.points[1].y, v.points[1].z, c.r, c.g, c.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { v.points[2].x, v.points[2].y, v.points[2].z, c.r, c.g, c.b });
	vertex_and_colors.insert(vertex_and_colors.end(), { v.points[3].x, v.points[3].y, v.points[3].z, c.r, c.g, c.b });
	indices.insert(indices.end(), { 0 + n, 1 + n, 3 + n });
	indices.insert(indices.end(), { 1 + n, 2 + n, 3 + n });
	n += 6;

}

void DrawSquare::setUpBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex_and_colors.size() * sizeof(float), vertex_and_colors.data(), GL_DYNAMIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glGenVertexArrays(1, &EBO);
		glGenBuffers(1, &EBO);

		// indices attribute
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);
}

void DrawSquare::useBuffers()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, vertex_and_colors.size(), GL_UNSIGNED_INT, 0);
}

void DrawSquare::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
