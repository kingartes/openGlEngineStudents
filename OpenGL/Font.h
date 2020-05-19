#pragma once
#include "includes/ft2build.h"
#include "includes/glm/vec2.hpp"
#include "includes/glm/mat4x4.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "includes/GLFW/glfw3.h"
#include <../shaders/shader.h>

#include <map>
#include FT_FREETYPE_H 

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font
{
public:
    Font() { };
    Font(std::map<char, Character> c) : Characters(c) { setBuffers(); }
    ~Font() { delete &Characters; };
    void drawText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

private:
    unsigned int VAO, VBO;
    std::map<char, Character> Characters;

    void setBuffers();
};

void Font::drawText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    shader.setMat4("projection", projection);
    // activate corresponding render state	
    shader.use();
    shader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character

        float vertices[6][4] =
        {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
}

void Font::setBuffers()
{
    // to see the text
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}