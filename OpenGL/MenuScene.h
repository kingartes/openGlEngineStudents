#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IScene.h"
#include "IInput.h"
#include "shaders/Shader.h"
#include "GameObject.h"
#include "camerar.h"
#include "ModelLoader.h"
#include "SceneRealization.h"
#include "Square.h"
#include "Font.h"
map<char, Character> loadFont(const char* path, int size);

class MenuScene:
    public IScene, public IInput
{
private:
    Shader* ourShader;
    Game* game;
    Font* font;
    Shader* textShader;

    //std::vector<GameObject*>* ourModels;

    Camera* camera;
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
    void setGame(Game* game) {
        this->game = game;
    }

    void IScene::Init() {
        this->game = game;
        ourShader = new Shader("shaders/Vertex.vs", "shaders/Pixel.fs");
        textShader = new Shader("shaders/VertexText.vs", "shaders/PixelText.ps");

        font = new Font(loadFont("Arimo-Regular.ttf", 128));

        std::vector<string> paths = { "resources/5/scene.gltf" };

        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
        //GameObjectModelLoadedFactory factory(paths, ourShader);

        //ourModels = new vector<GameObject*>();
        //std::vector <GameObject*> o1 = factory.loadAll();
        //ourModels->insert(ourModels->begin(), o1.begin(), o1.end());
        //camera->Position = glm::vec3(0, 10, 0);
        Square *s = new Square("resources/test.jpg");
        GameObject* square = s->getSquare();
        //std::cout << ourModels->size() << "\n";
        this->setInput(this);
    }
    void IScene::draw(float deltaTime) {
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
        font->drawText(*textShader, "Hello World", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        //ourModels->at(0)->Draw(ourShader);
    }

    void IScene::onResize(float width, float height) {}

    void processInput(GLFWwindow* window, float deltaTime) {
        if (glfwGetKey(window, /*GLFW_KEY_ESCAPE*/GLFW_KEY_SPACE) == GLFW_PRESS) {
            //Game* g = this->getGame();
            game->setScene(new SceneRealization());
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        /*
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

        camera->ProcessMouseMovement(xoffset, yoffset);*/
    }
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        //camera->ProcessMouseScroll(yoffset);
    }
    void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    }
};

map<char, Character> loadFont(const char* path, int size)
{
    map<char, Character> Characters;
    FT_Library ft;
    FT_Face face;

    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(ft, path, 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return Characters;
}