#include "Font.h"
#include <sstream>
#include <freetype\ftglyph.h>
bool Font::isInit;
FT_Library Font::ft;
std::map<std::string,Font*> Font::loadedFonts;

Font::Font(std::string name,int size){
	if(!isInit){
		if (FT_Init_FreeType(&ft)) {
			fprintf(stderr, "Could not init freetype library\n");
			return;
		}
	}
	if (FT_New_Face(ft, name.c_str(), 0, &face)) {
		fprintf(stderr, "Could not open font %s\n", name);
		return;
	}	
	fontSize = size;
	FT_Set_Pixel_Sizes(face, 0, size);
}

GlyphCash Font::renderChar(char c){
	std::map<char, GlyphCash>::iterator it = glyphCash.find(c);
	if(it != glyphCash.end())
		return it->second;
	FT_Load_Char( face, c, FT_LOAD_RENDER ); 
	GlyphCash g = GlyphCash(face->glyph->bitmap, face->glyph->bitmap_left, face->glyph->bitmap_top);
	glyphCash.insert(it,std::pair<char, GlyphCash> (c, g));
	return g;
}

Font* Font::getFont(std::string fileName,int size){
	std::ostringstream s;
	s << size << fileName;
	std::string query(s.str());
	std::map<std::string,Font*>::iterator it = loadedFonts.find(query);
	if(it != loadedFonts.end())
		return it->second;
	Font* font = new Font(fileName, size);
	loadedFonts.insert(std::pair<std::string, Font*>(query, font));
	return font;
}

int Font::getSize(){
	return fontSize;
}

int Font::getKerning(char prev, char cur){
	FT_Vector  delta;
	FT_Get_Kerning( face, prev, cur,
						  FT_KERNING_DEFAULT, &delta );
	return delta.x;
}

GlyphCash::GlyphCash(FT_Bitmap bitmap_, int left, int top){
	bitmap_left = left;
	bitmap_top = top;
	bitmap = bitmap_;
	int pitch = bitmap.pitch;
	if (pitch < 0) pitch = -pitch;
	bitmap.buffer = new  unsigned char[bitmap.rows*pitch];
	std::memcpy(bitmap.buffer
					, bitmap_.buffer, pitch*bitmap.rows);
}

GlyphCash::GlyphCash()
{

}