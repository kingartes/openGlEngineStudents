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
#include "SkyBox.h"
class SceneRealization :
	public IScene, public IInput
{
private:
	Shader *ourShader;
    Shader* skyBoxShader;

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
    std::vector<glm::vec4>* planetD;

    GameObject* skybox;
public:
    void IScene::Init() {
        vector<string> faces{
             "resources/test.jpg",
             "resources/test.jpg",
             "resources/test.jpg",
             "resources/test.jpg",
             "resources/test.jpg",
             "resources/test.jpg"
        };
        SkyBox s(faces);
        skybox = s.create();

        SpaceGenerator *generator = new SpaceGenerator();
        planetD = new std::vector<glm::vec4>();
        planetD = generator->PlanetCoordCreate(50);

        this->setInput(this);
        
        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        
        
        ourShader = new Shader("shaders/Vertex.vs", "shaders/Pixel.fs");
        skyBoxShader = new Shader("shaders/skybox.vs", "shaders/skybox.fs");
        
        std::vector<string> paths = {"resources/5/scene.gltf"};
        
        
        GameObjectModelLoadedFactory factory(paths, ourShader);

        ourModels = new vector<GameObject*>();
        std::vector <GameObject*> o1 = factory.loadAll();
        ourModels->insert(ourModels->begin(), o1.begin(), o1.end());
       
        //camera->Position = glm::vec3(0, 10, 0);
        std::cout << ourModels->size() << "\n";

        for (int i = 0; i < planetD->size()-1; i++) {
            glm::vec4 c = (glm::vec4)planetD->at(i);
            std::cout << c.x << " " << c.y << " " << c.z << " " << c.w << std::endl;
        }
    }
	void IScene::draw(float deltaTime) {

        f += 0.005;


        //backgroundShader->use();

        //background->Draw(backgroundShader);

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

        ourShader->setVec3("lightPos", glm::vec3(sin(f)*10, 0, cos(f)*10));
        
        for (int i = 0; i < planetD->size()-1; i++) {

            glm::mat4 model = glm::mat4(1.0f);
            //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
            glm::vec4 c = (glm::vec4)planetD->at(i);
           
            //model *= ourModels->at(i)->getTransform();
            model = glm::translate(model, glm::vec3(c.x, c.y, c.z));
            model = glm::scale(model, glm::vec3(c.w, c.w, c.w));
            //model = glm::scale(model, glm::vec3(c.w, c.w, c.w));

            ourShader->setMat4("model", model);

            ((GameObject*)ourModels->at(0))->Draw(ourShader);
        }
        glDepthFunc(GL_LEQUAL);
        skyBoxShader->use();

        // change depth function so depth test passes when values are equal to depth buffer's content
        view = glm::mat4(glm::mat3(camera->GetViewMatrix())); // remove translation from the view matrix
        skyBoxShader->setMat4("view", view);
        skyBoxShader->setMat4("projection", projection);

        skybox->Draw(skyBoxShader);
        glDepthFunc(GL_LESS); // set depth function back to default*/
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