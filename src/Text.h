#pragma once
#include <map>
#include <string>
#include "defs.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#define string std::string
#define map std::map
#include "GraphicShape.h"
#include "Font.h"
#include "Texture.h"

class Text : public GraphicShape{
private:
	Font* font;
	string text;
	int lineSpacing;
	int letterSpacing;
	int wordSpacing;
	bool changed;
	Texture* texture;
	void renderTexture();
	bool kerning;
	int fontHeight, fontWidth,   //texture size is font  
			texHeight, texWidth; //size supplemented to power of two 
	float color[4];
	bool colorful;
	static int addToPowerOfTwo(int i);
	GLuint textureNum;
public:
	Text* Text::setX(int x_);
	Text* Text::setY(int y_);
	Text* setColor(float red, float green, float blue, float alpha);
	Text* setText(string newText);
	Text* setLineSpacing(int n);
	Text* setLetterSpacing(int n);
	Text* setWordSpacing(int n);
	Text* setFont(string fileName,int size);
	Text* setFontHeight(int h); // height in pixels
	void draw();
	Text();
};