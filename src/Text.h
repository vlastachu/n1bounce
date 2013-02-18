#pragma once
#include <GL/glew.h>
#include <string>
#include "defs.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Font.h"

class Text {
private:
	int x,y;
	Font* font;
	std::string text;
	int lineSpacing;
	int letterSpacing;
	int wordSpacing;
	bool changed;
	void renderTexture();
	bool kerning;
	int fontHeight, fontWidth,   //texture size is font  
			texHeight, texWidth; //size supplemented to power of two 
	float color[4];
	static int addToPowerOfTwo(int i);
	GLuint textureNum;
public:
	Text* Text::setX(int x_);
	Text* Text::setY(int y_);
	Text* setColor(float red, float green, float blue, float alpha);
	Text* setText(std::string newText);
	Text* setLineSpacing(int n);
	Text* setLetterSpacing(int n);
	Text* setWordSpacing(int n);
	Text* setFont(std::string fileName,int size);
	Text* setFontHeight(int h); // height in pixels
	void draw();
	Text();
};