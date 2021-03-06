#pragma once
#include <GLFW/glfw3.h>
#include "IInput.h"
class IScene
{
private:
	GLFWwindow* window;
	IInput* input;
	//Game* game;
public:
	virtual void draw(float deltaTime) = 0;
	virtual void onResize(float width, float height) = 0;
	virtual void Init() = 0;
	void setWindow(GLFWwindow* window) { this->window = window; };
	IInput* getInput() { return this->input; };
	void setInput(IInput* input) { this->input = input; };
	//void setGame(Game* game) { this->game = game; };
	//Game* getGame() { return this->game; };
};

