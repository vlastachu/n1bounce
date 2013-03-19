#include "Font.h"
#include <sstream>
#include <freetype\ftglyph.h>
bool Font::isInit;
FT_Library Font::ft;
std::map<std::string,Font*> Font::loadedFonts;

Font::Font(std::string name,int size){
	glGenTextures(1,&texture);
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
	
	//calculateSizes();
	unsigned char *data = new unsigned char[fontSize*fontSize*64*64];
	for(unsigned int i = 0; i < fontSize*fontSize*64*64;i++) data[i] = 0;
	int left = 0, top = 0; 
	for(unsigned int k = 0; k < 64; k++){
		for(unsigned int i = 0; i < 64; i++){	
		FT_Load_Char( face, (char)(k*64 + i), FT_LOAD_RENDER ); 
			int pitch = face->glyph->bitmap.pitch;
			if (pitch < 0) pitch = -pitch;
			for (int row = 0; row < face->glyph->bitmap.rows; ++row) 
				std::memcpy(data + left + 64*fontSize*(row + top)
					, face->glyph->bitmap.buffer + pitch * row, pitch);

			GlyphCash g = GlyphCash(i/64.0,k/64.0,face->glyph->bitmap.width/(fontSize*64.0),face->glyph->bitmap.rows/(fontSize*64.0),face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_left, fontSize-face->glyph->bitmap_top);
			glyphCash.insert(glyphCash.end(),std::pair<char, GlyphCash> ((char)(k*64 + i), g));
			left += fontSize;
		}
		top += fontSize;
		left = 0;
	}
	glBindTexture(GL_TEXTURE_2D,texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 64*fontSize, 64*fontSize, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	delete data;
}

void Font::renderTexture(){
}

GlyphCash Font::renderChar(char c){
	std::map<char, GlyphCash>::iterator it = glyphCash.find(c);
		return it->second;
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

