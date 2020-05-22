#pragma once
#include "Font.h"
#include "FontLoader.h"

class FontFactory
{
public:
	FontFactory() { loader = new FontLoader(); }
	FontFactory(std::vector<const char*> paths) { this->paths = paths; loader = new FontLoader(); }
	~FontFactory() { delete loader; }
	std::vector<Font*> loadAll()
	{
		std::vector<Font*> fonts;
		Font* font;
		for (unsigned int i = 0; i < paths.size(); i++)
		{
			loader->loadFont(paths[i], 128);
			font = new Font(loader->getCharacters());
			fonts.push_back(font);
		}
		font = new Font();
		delete font;
		return fonts;
	}

private:
	std::vector <const char*> paths;
	FontLoader* loader;
};