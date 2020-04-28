#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IScene.h"
#include "IInput.h"
#include "shaders/Shader.h"
#include "GameObject.h"
#include "shaders/shader.h"
#include "camerar.h"
#include <iostream>
#include "ModelLoader.h"
#include "GameObjectModelLoadedFactory.h"
#include "ParallelogramLoader.h"
#include "SpaceGenerator.h"
class SceneRealization :
	public IScene, public IInput
{
private:
	Shader *ourShader;
    std::vector<GameObject*> *ourModels;
    Camera *camera;
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
    std::vector<glm::vec4> *planetD;
public:
    void IScene::Init() {
        SpaceGenerator *generator = new SpaceGenerator();
        planetD = generator->PlanetCoordCreate(200);
        this->setInput(this);
        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        ourShader = new Shader("shaders/Vertex.vs", "shaders/Pixel.ps");
        
        std::vector<string> paths = {"resources/4/scene.gltf"};
        GameObjectModelLoadedFactory factory(paths, ourShader);

        ourModels = new vector<GameObject*>();
        std::vector <GameObject*> o1 = factory.loadAll();
        ourModels->insert(ourModels->begin(), o1.begin(), o1.end());
        //ParallelogramLoader* m = new ParallelogramLoader(ourShader);
        //ourModels->push_back(m->getModel());
        //
    }
	void IScene::draw(float deltaTime) {
        //f += 0.005;

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
        
        ourShader->setVec3("viewPos", glm::vec3(camera->Position.x, camera->Position.y, camera->Position.z));
       
        ourShader->setVec3("lightPos", glm::vec3(100 * cos(f), 20, 80*sin(f)));
        ourModels->at(0)->setTransform(glm::rotate(glm::mat4(1.0f), glm::radians(f*10), glm::vec3(0.0f, f, 0.0f)));
        //camera->Position.x = 10 * cos(f);
        //camera->Position.z = 10 * sin(f);

        const float x = -2.0f;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, 0, x)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down

        camera->Position.x = x;
        camera->Position.y = 0;
        camera->Position.z = x ;

        ourShader->setMat4("model", model);

        ((GameObject*)ourModels->at(0))->Draw(ourShader);

        for (int i = 0; i < planetD->size(); i++) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

            model = glm::translate(model, glm::vec3(planetD->at(i).x, planetD->at(i).y, planetD->at(i).z));
            model = glm::scale(model, glm::vec3(planetD->at(i).w, planetD->at(i).w, planetD->at(i).w));

            ourShader->setMat4("model", model);

            ((GameObject*)ourModels->at(0))->Draw(ourShader);
        }

                
	}

	void IScene::onResize(float width, float height) {}

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