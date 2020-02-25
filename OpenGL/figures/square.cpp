#include "square.hpp"
#include <glad/glad.h>

Square::Square()
{
	vs = "shaders/Vertex.vs";
	vp = "shaders/Pixel.ps";
	vertex = {};
}

Square::Square(square v, color c)
{
	vs = "shaders/Vertex.vs";
	vp = "shaders/Pixel.ps";
	vertex = {};
	add(v, c);
}

Square::~Square()
{
	deleteBuffers();
}

void Square::add(square v, color c)
{
	vertex.insert(vertex.end(), { v.points[0].x, v.points[0].y, v.points[0].z, c.r, c.g, c.b });
	vertex.insert(vertex.end(), { v.points[1].x, v.points[1].y, v.points[1].z, c.r, c.g, c.b });
	vertex.insert(vertex.end(), { v.points[2].x, v.points[2].y, v.points[2].z, c.r, c.g, c.b });
	vertex.insert(vertex.end(), { v.points[3].x, v.points[3].y, v.points[3].z, c.r, c.g, c.b });
	indices.insert(indices.end(), { 0, 1, 3 });
	indices.insert(indices.end(), { 1, 2, 3 });
}

void Square::setShaders(const char* v, const char* p)
{
	vs = v;
	vp = p;
}

void Square::setUpBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), vertex.data(), GL_DYNAMIC_DRAW);

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

void Square::useBuffers()
{
	Shader shader(vs, vp);
	shader.use();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, vertex.size(), GL_UNSIGNED_INT, 0);
}

void Square::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}