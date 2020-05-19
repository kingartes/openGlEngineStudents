#pragma once
#include "FontLoader.h"
#include "Font.h"
#include <vector>

class TextLoaderFactory
{
public:
	TextLoaderFactory();
	~TextLoaderFactory();

private:
	std::vector<Font> fonts;
};

TextLoaderFactory::TextLoaderFactory()
{
}

TextLoaderFactory::~TextLoaderFactory()
{
}