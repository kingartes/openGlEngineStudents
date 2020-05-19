#pragma once
#include "includes/glm/vec2.hpp"
#include "includes/GLFW/glfw3.h"

#include <map>
#include <iostream>
#include "includes/ft2build.h"
#include FT_FREETYPE_H 

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class FontLoader
{
public:
    FontLoader() {};
    FontLoader(const char* path, int size) { loadFont(path, size); deleteFont(); };
    std::map<char, Character> getCharacters() { return Characters; }
    ~FontLoader() { deleteFont(); };

private:
    std::map<char, Character> Characters;
    FT_Library ft;
    FT_Face face;

    void loadFont(const char* path, int size)
    {
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
    }
    void deleteFont()
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    };
};