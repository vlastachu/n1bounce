#pragma once
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
	void drawText(int dx, int dy);
	GLuint textureNum;
	bool shadow; float outline;
	int shadowDx, shadowDy;
	float shadowColor[4], outlineColor[4];
public:
	float getHeight();
	float getWidth();
	Text* setShadow(bool onOff, int dx, int dy, float red, float green, float blue, float alpha);
	Text* setOutline(float size, float red, float green, float blue, float alpha);
	Text* setX(int x_);
	Text* setY(int y_);
	Text* calculateSizes();
	Text* setColor(float red, float green, float blue, float alpha);
	Text* setText(std::string newText);
	Text* setLineSpacing(int n);
	Text* setLetterSpacing(int n);
	Text* setWordSpacing(int n);
	Text* setFont(std::string fileName,int size);
	Text* setFontHeight(int h); // height in pixels
	Text* setKerning(bool k);
	void draw();
	Text();
};