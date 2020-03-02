#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <../includes/stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "figures/square.hpp"
GLFWwindow* window;
int InitApp();
// sets files direction and returns id
// jpg format doesn`t work
unsigned int setTexure(char const* dir);

int main()
{
	using glm::vec2;
	using glm::vec3;
	using glm::vec4;

	square check2 =
	{
		vec4(0.5, 0.5, 0.0, 1.0),
		vec4(0.5, -0.5, 0.0, 1.0),
		vec4(-0.5, -0.5, 0.0, 1.0),
		vec4(-0.5, 0.5, 0.0, 1.0)
	};

	Square drs = Square(check2, color{ 0.8, 0.2, 0.0 }, text{ vec2({ 1, 0 }), vec2({ 1, 1}), vec2({ 0, 1 }), vec2({ 0, 0  }) });

	if (!InitApp()) 
	{
		drs.setUpBuffers();
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			unsigned int texture = setTexure("container2.png");
			drs.setTexure(texture);
			drs.useBuffers();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		drs.deleteBuffers();
		glfwTerminate();
	}
	else
		return -1;

	return 0;
}


int InitApp()
{
	// glfw: initialize and configure
	// ------------------------------
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for OSX
#endif
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;
	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

unsigned int setTexure(char const* dir)
{
	// jpg format doesn`t work
	unsigned int texture;
	glGenTextures(1, &texture);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(dir, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_DEPTH_STENCIL;
			
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
		std::cout << "Texture failed to load at path: " << dir << std::endl;

	stbi_image_free(data);

	return texture;
}