#include "Text.h"
#include <wchar.h>
#include <ft2build.h>
#include <limits>
#include <list>
#include <GL/glew.h>
#include "defs.h"
void Text::renderTexture(){
	//немного бесполезный труд, но что поделать
	//высчитаю конечную ширину текстуры и округлю до степени двойки
	fontWidth = texHeight = texWidth = 20;//таки погрешность 
	texHeight = fontHeight = font->getSize();	
	GlyphCash g;
    for(unsigned int i = 0; i < text.size(); i++){
		if(text[i] == ' ') fontWidth += wordSpacing; else
		if(text[i] == '\n') texHeight += font->getSize() + lineSpacing; else
		{
			g = font->renderChar(text[i]);
			fontWidth += g.bitmap.width;//->advance.x >> 6;  вот отсюда растёт погрешность. костыль так сказать
			fontWidth += g.bitmap_left;
			fontWidth += letterSpacing;
			if(kerning && i > 1)
				fontWidth += font->getKerning(text[i-1],text[i]);
		}
	}
	texHeight = addToPowerOfTwo(texHeight);
	texWidth = addToPowerOfTwo(fontWidth);
	//TODO: calculating of hight width
	int strSize = text.size();
	unsigned char *data = new unsigned char[texHeight*texWidth];
	for(unsigned int i = 0; i < texHeight*texWidth;i++) data[i] = 0;
	int left = 0, top = 0; 
	for(unsigned int i = 0; i < strSize; i++){
		if(text.at(i) == ' ') left += wordSpacing; else
			if(text.at(i) == '\n'){ top += fontHeight + lineSpacing; left = 0;}
		else
		{
			g = font->renderChar(text.at(i));
			if(!kerning || i < 2)
				left += g.bitmap_left + letterSpacing;
			else
				left += g.bitmap_left + letterSpacing + font->getKerning(text[i-1],text[i]);
			int pitch = g.bitmap.pitch;
			if (pitch < 0) pitch = -pitch;
			for (int row = 0; row < g.bitmap.rows; ++row) 
			{
				if(!kerning)
				std::memcpy(data + left + texWidth*(row + fontHeight - g.bitmap_top + top)
					, g.bitmap.buffer + pitch * row, pitch);
				else
					for(int b = 0; b < pitch; b++){
						if(data[left + texWidth*(row + fontHeight -  g.bitmap_top + top) + b] + g.bitmap.buffer[pitch * row + b] < UCHAR_MAX)
							data[left + texWidth*(row + fontHeight -  g.bitmap_top + top) + b] += g.bitmap.buffer[pitch * row + b];
						else
							data[left + texWidth*(row + fontHeight -  g.bitmap_top + top) + b] = UCHAR_MAX;
					}
			}
			left += g.bitmap.width;
		}
		
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	
	glBindTexture(GL_TEXTURE_2D,textureNum);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texWidth, texHeight, GL_RED, GL_UNSIGNED_BYTE, data);
	delete data;
}
	Text* Text::setText(std::string newText){
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
		   glEnable (GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		GLint swizzleMask[] = {GL_ZERO, GL_ZERO, GL_ZERO, GL_RED};
		glTexParameteriv(GL_TEXTURE_2D, 0x8E46, swizzleMask); // 0x8E46 is GL_TEXTURE_SWIZZLE_RGBA 
		if(shadow)
		{
			glColor4f(shadowColor[0],shadowColor[1],shadowColor[2],shadowColor[3]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
			glBindTexture(GL_TEXTURE_2D,textureNum);		
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);glVertex2f(x + shadowDx, y + shadowDy); //top left
			  glTexCoord2f(1.0f, 0.0f);glVertex2f(x + texWidth + shadowDx, y + shadowDy); //top right
			  glTexCoord2f(1.0f, 1.0f);glVertex2f(x + texWidth + shadowDx,y + texHeight + shadowDy); // bottom right
			  glTexCoord2f(0.0f, 1.0f);glVertex2f(x + shadowDx, y + texHeight + shadowDy); //bottom left
			glEnd();
		}
		glColor4f(color[0],color[1],color[2],color[3]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,textureNum);
		
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, 0.0f);glVertex2f(x, y); //top left
		  glTexCoord2f(1.0f, 0.0f);glVertex2f(x + texWidth, y); //top right
		  glTexCoord2f(1.0f, 1.0f);glVertex2f(x + texWidth,y + texHeight); // bottom right
		  glTexCoord2f(0.0f, 1.0f);glVertex2f(x ,y + texHeight); //bottom left
		glEnd();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	
	
	Text* Text::setShadow(bool onOff, int dx, int dy, float red, float green, float blue, float alpha)
	{
		shadow = onOff;
		shadowDx = dx;
		shadowDy = dy;
		shadowColor[0] = red;
		shadowColor[1] = green;
		shadowColor[2] = blue;
		shadowColor[3] = alpha;
		changed = true;
		return this;
	}

	Text* Text::setFont(std::string fileName,int size)
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
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = alpha;
		return this;
	}

	Text* Text::setKerning(bool k)
	{
		kerning = k;
		changed = true;
		return this;
	}
	Text::Text(){
		kerning = false;
		changed = true;
		color[0] = 0.;
		color[1] = 0.;
		color[2] = 0.;
		color[3] = 1.;
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