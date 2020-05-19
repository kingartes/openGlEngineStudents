#pragma once
class IInput
{
public:
	virtual void mouse_callback(GLFWwindow*, double, double) = 0;
	virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) = 0;
	virtual void processInput(GLFWwindow* window, float deltaTime) = 0;
	virtual void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};

