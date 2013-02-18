#include "Text.h"
#include <wchar.h>
#include <ft2build.h>
#include <limits>
#include <list>
#include "defs.h"
void Text::renderTexture(){
	//немного бесполезный труд, но что поделать
	//высчитаю конечную ширину текстуры и округлю до степени двойки
	fontWidth = texHeight = texWidth = 0;
	fontHeight = font->getSize();
	GlyphCash g;
    for(unsigned int i = 0; i < text.size(); i++){
		if(text[i] == ' ') fontWidth += wordSpacing; else
		if(text[i] == '\n') fontHeight += font->getSize() + lineSpacing; else
		{
			g = font->renderChar(text[i]);
			fontWidth += g.bitmap.width;//->advance.x >> 6;
			fontWidth += g.bitmap_left;
			fontWidth += letterSpacing;
			if(kerning && i > 1)
				fontWidth += font->getKerning(text[i-1],text[i]);
		}
	}
	texHeight = Texture::addToPowerOfTwo(fontHeight);
	texWidth = Texture::addToPowerOfTwo(fontWidth);
	//TODO: calculating of hight width
	int strSize = text.size();
	unsigned char *data = new unsigned char[texHeight*texWidth];
	for(unsigned int i = 0; i < texHeight*texWidth;i++) data[i] = 0;
	int left = 0, top = 0; 
	for(unsigned int i = 0; i < strSize; i++){
		if(text.at(i) == ' ') left += wordSpacing; else
		if(text.at(i) == '\n') top += fontHeight + lineSpacing; else
		{
			g = font->renderChar(text.at(i));
			int pitch = g.bitmap.pitch;
			if (pitch < 0) pitch = -pitch;
			for (int row = 0; row < g.bitmap.rows; ++row) 
			{
				if(!kerning)
				std::memcpy(data + left + texWidth*(row + fontHeight -  g.bitmap_top)
					, g.bitmap.buffer + pitch * row, pitch);
				else
					for(int b = 0; b < pitch; b++){
						if(data[left + texWidth*(row + fontHeight -  g.bitmap_top) + b] + g.bitmap.buffer[pitch * row + b] < UCHAR_MAX)
							data[left + texWidth*(row + fontHeight -  g.bitmap_top) + b] += g.bitmap.buffer[pitch * row + b];
						else
							data[left + texWidth*(row + fontHeight -  g.bitmap_top) + b] = UCHAR_MAX;
					}
			}
		}
		if(!kerning || i < 2)
			left += g.bitmap_left + g.bitmap.width + letterSpacing;
		else
			left += g.bitmap_left + g.bitmap.width + letterSpacing + font->getKerning(text[i-1],text[i]);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	
	//glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	if(colorful)
	{
		glColor4f(color[0],color[1],color[2],color[3]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	}
	glBindTexture(GL_TEXTURE_2D,textureNum);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texWidth, texHeight, GL_RED, GL_UNSIGNED_BYTE, data);
}
	Text* Text::setText(string newText){
		text = newText;
		changed = true;
		return this;
	}
	Text* Text::setLineSpacing(int n){
		lineSpacing = n;
		changed = true;
		return this;
	}
	Text* Text::setLetterSpacing(int n){
		letterSpacing = n;
		changed = true;
		return this;
	}
	Text* Text::setWordSpacing(int n){
		wordSpacing = n;
		changed = true;
		return this;
	}
	void Text::draw(){
		if(changed){
			renderTexture();
			changed = false;
		}
		GLint swizzleMask[] = {GL_ZERO, GL_ZERO, GL_ZERO, GL_RED};
		glTexParameteriv(GL_TEXTURE_2D, 0x8E46, swizzleMask); // 0x8E46 is GL_TEXTURE_SWIZZLE_RGBA 
		glBindTexture(GL_TEXTURE_2D,textureNum);
		glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, 0.0f);glVertex2f(x, y); //top left
		  glTexCoord2f(1.0f, 0.0f);glVertex2f(x + texWidth, y); //top right
		  glTexCoord2f(1.0f, 1.0f);glVertex2f(x + texWidth,y + texHeight); // bottom right
		  glTexCoord2f(0.0f, 1.0f);glVertex2f(x ,y + texHeight); //bottom left
		glEnd();
		GLint swizzleMask1[] = {GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA};
		glTexParameteriv(GL_TEXTURE_2D, 0x8E46, swizzleMask1); // 0x8E46 is GL_TEXTURE_SWIZZLE_RGBA 
	}
	
	Text* Text::setFont(string fileName,int size)
	{
		font = Font::getFont(fileName,size);
		changed = true;
		return this;
	}

	Text* Text::setX(int x_)
	{
		x = x_;
		changed = true;
		return this;
	}

	Text* Text::setY(int y_)
	{
		y = y_;
		changed = true;
		return this;
	}

	Text* Text::setColor(float red, float green, float blue, float alpha){
		changed = true;
		colorful = true;
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = alpha;
		return this;
	}

	Text::Text(){
		kerning = false;
		changed = true;
		colorful = false;
		wordSpacing = 15;
		letterSpacing = 0;
		lineSpacing = 20;
		x = y = 50;
		glGenTextures(1,&textureNum);
	}
	
int Text::addToPowerOfTwo(int i){
	int j = 1;
	while (j < i) 
		j = j << 1;
	return j;
}