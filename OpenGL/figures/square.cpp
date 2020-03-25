#include "square.hpp"
#include <glad/glad.h>

Square::Square()
{
	vs = "shaders/Vertex.vs";
	vp = "shaders/Pixel.ps";
	vertex = {};
}

Square::Square(square v, color c, text t)
{
	vs = "shaders/Vertex.vs";
	vp = "shaders/Pixel.ps";
	vertex = {};
	add(v, c, t);
}

Square::~Square()
{
	deleteBuffers();
}

void Square::add(square v, color c, text te)
{
	vertex.insert(vertex.end(), { v.points[0].x, v.points[0].y, v.points[0].z, c.r, c.g, c.b, te.t[0].x, te.t[0].y });
	vertex.insert(vertex.end(), { v.points[1].x, v.points[1].y, v.points[1].z, c.r, c.g, c.b, te.t[1].x, te.t[1].y  });
	vertex.insert(vertex.end(), { v.points[2].x, v.points[2].y, v.points[2].z, c.r, c.g, c.b, te.t[2].x, te.t[2].y  });
	vertex.insert(vertex.end(), { v.points[3].x, v.points[3].y, v.points[3].z, c.r, c.g, c.b, te.t[3].x, te.t[3].y  });
	indices.insert(indices.end(), { 0, 1, 3 });
	indices.insert(indices.end(), { 1, 2, 3 });
}

void figure::setUpBuffers()
{
	shader = Shader(vs, vp);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), vertex.data(), GL_DYNAMIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// texture attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glGenVertexArrays(1, &EBO);
		glGenBuffers(1, &EBO);

		// indices attribute
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
}

void figure::useBuffers()
{
	shader.use();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void figure::setTexure(unsigned int texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, vertex.size(), GL_UNSIGNED_INT, 0);
}

void figure::deleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}