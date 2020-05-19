#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "IInput.h"
#include "IScene.h"

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
   /* void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);*/
    void processInput(GLFWwindow* window);

class Game
{
public:
	Game(IScene* scene);
    void setScene(IScene* scene);
    void start();
	~Game();
private:
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	IScene* scene;
	IInput* input;

    GLFWwindow* window;

	void initialization() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
        #endif

    // glfw window creation
    // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine-0.0.1-dev-3", NULL, NULL);
        scene->setWindow(window);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit( -1);
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        auto framebuffer_size_func = [](GLFWwindow* window, int width, int height)
        {
            static_cast<Game*>(glfwGetWindowUserPointer(window))->framebuffer_size_callback(window, width, height);
        };
        glfwSetFramebufferSizeCallback(window, framebuffer_size_func);
        auto mousefunc = [](GLFWwindow* window, double xpos, double ypos)
        {
            static_cast<Game*>(glfwGetWindowUserPointer(window))->input->mouse_callback(window, xpos, ypos);
        };
        glfwSetCursorPosCallback(window, mousefunc);
        auto scrollfunc = [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<Game*>(glfwGetWindowUserPointer(window))->input->scroll_callback(window, xoffset, yoffset);
        };
        glfwSetScrollCallback(window, scrollfunc);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        // build and compile shaders
        // -------------------------
        scene->Init();
        input = scene->getInput();
	}

    /* Callbacks */
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        scene->onResize(width, height);
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
    void processInput(GLFWwindow* window)
    {
        input->processInput(window, deltaTime);
    }
};
void Game::start() {
    initialization();
    std::cout << "init complete" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------

        scene->draw(deltaTime);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    exit(0);
}

void Game::setScene(IScene* scene) {
    std::cout << this << std::endl;
    if (this->scene == nullptr) 
        std::cout << "nullptr" << std::endl;
    else
        this->scene = scene;    
    //scene->setGame(this);
    scene->setWindow(window);
    scene->Init();
    input = scene->getInput();
}

Game::Game(IScene* scene)
{
    this->scene = scene;
    //scene->setGame(this);
}

Game::~Game()
{
}
