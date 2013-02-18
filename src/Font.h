#pragma once
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "defs.h"
#define string std::string
#define map std::map

struct GlyphCash{
		FT_Bitmap bitmap;
		int bitmap_left;
		int bitmap_top;
		GlyphCash(FT_Bitmap bitmap_, int left, int top);
		GlyphCash();
	};

class Font{
private:
	map<char, GlyphCash> glyphCash;
	static map<string,Font*> loadedFonts;
	string fontName;
	int fontSize;
	static FT_Library ft;
	static bool isInit;
	FT_Face face;
	Font(string name,int size);
public:
	GlyphCash renderChar(char c);
	static Font* getFont(string fileName,int size);  //get font from ttf file
	int getSize();
	int getKerning(char prev, char cur);
};