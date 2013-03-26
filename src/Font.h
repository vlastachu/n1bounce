#pragma once
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "defs.h"
using std::string;
struct GlyphCash{
		float texX, texY, texW,texH,realW,realH;

		int bitmap_left;
		int bitmap_top;
		GlyphCash(float x, float y, float w, float h,float rw, float rh, int left, int top):texX(x),texY(y), texW(w),texH(h),realW(rw),realH(rh),bitmap_left(left),bitmap_top(top){}
		GlyphCash(){}
	};

class Font{
private:
	std::map<char, GlyphCash> glyphCash;
	static std::map<std::string,Font*> loadedFonts;
	std::string fontName;
	int fontSize;
	static FT_Library ft;
	static bool isInit;
	FT_Face face;
	Font(std::string name,int size);
	void renderTexture();
public:
	string texture;
	GlyphCash renderChar(char c);
	static Font* getFont(std::string fileName,int size);  //get font from ttf file
	int getSize();
	int getKerning(char prev, char cur);
};