#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IScene.h"
#include "IInput.h"
#include "shaders/Shader.h"
#include "Model.h"
#include "shaders/shader.h"
#include "camerar.h"
#include "Model.h"
#include <iostream>

class Pause :
    public IScene, public IInput
{
private:
    Shader* ourShader;
    Model* ourModel;
    Model* ourModel1;
    Camera* camera;
    float f = 0;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    // camera
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;
    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
public:
    void IScene::Init() {
        this->setInput(this);
        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        ourShader = new Shader("shaders/Vertex.vs", "shaders/Pixel.ps");
        // load models
        // -----------
        ourModel = new Model("C:/Users/matro/Source/Repos/openGlEngineStudents/OpenGL/resources/3/scene.gltf");
        ourModel1 = new Model("C:/Users/matro/Source/Repos/openGlEngineStudents/OpenGL/resources/1/scene.gltf");

        //this->setControll(this);
    }
    void IScene::draw(float deltaTime) {
        f += 0.01;

        // render
        // ------
        glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        ourShader->setMat4("projection", projection);
        ourShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        ourShader->setMat4("model", model);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, f));
        trans = glm::rotate(trans, 3.1415f, glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(3.0f, 3.0f, 3.0f));
        ourModel->setTransform(trans);
        ourModel->Draw(*ourShader);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, -3.0f, f - 1.f));
        ourModel1->setTransform(trans);
        ourModel1->Draw(*ourShader);

    }

    void IScene::onResize(float width, float height) {

    }

    void processInput(GLFWwindow* window, float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->ProcessKeyboard(RIGHT, deltaTime);
    }
    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        camera->ProcessMouseScroll(yoffset);
    }
    void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    }
};