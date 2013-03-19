#define __ARB_ENABLE true
#include "Text.h"
#include <wchar.h>
#include <ft2build.h>
#include <limits>
#include <list>
#include "defs.h"

	Text* Text::calculateSizes(){
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
				fontWidth += g.realW;//->advance.x >> 6;  вот отсюда растёт погрешность. костыль так сказать
				fontWidth += g.bitmap_left;
				fontWidth += letterSpacing;
				if(kerning && i > 1)
					fontWidth += font->getKerning(text[i-1],text[i]);
			}
		}
		texHeight = addToPowerOfTwo(texHeight);
		texWidth = addToPowerOfTwo(fontWidth);
	return this;
	}


	/*void Font::renderTexture(){
	//calculateSizes();
		GlyphCash g;
	unsigned char *data = new unsigned char[fontSize*fontSize*];
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
		
	}*/
	float Text::getHeight()
	{
		return (fontHeight*1.0 + 2*outline + shadowDy*1.0);
	}
	float Text::getWidth()
	{
		return fontWidth;
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
	glEnable (GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,font->texture);
		if(outline!= 0.0)
		{
			glColor4f(outlineColor[0],outlineColor[1],outlineColor[2],outlineColor[3]);
			int detalization = 4*((int)outline*(int)outline);
			float Dx, Dy;
			for(float i = 0.0; i <= PI*2; i += PI*2/detalization)
			{
				Dx = outline*cos(i), Dy = outline*sin(i);
				drawText(Dx, Dy);
			}
		}
		if(shadow)
		{
			glColor4f(shadowColor[0],shadowColor[1],shadowColor[2],shadowColor[3]);
			drawText(shadowDx,shadowDy);
		}
		glColor4f(color[0],color[1],color[2],color[3]);
		drawText(0,0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
	
	void Text::drawText(int dx, int dy)
	{
		float left = 0, top = 0;
		for(int i = 0; i < text.size(); i++){
			if(text.at(i) == ' ') left += wordSpacing; else
				if(text.at(i) == '\n'){ top += fontHeight + lineSpacing; left = 0;}
			else
			{
				GlyphCash g = font->renderChar(text[i]);
				left += g.bitmap_left;
				if(kerning && i > 0) left += font->getKerning(text[i-1],text[i]);
				glBegin(GL_QUADS);
					glTexCoord2f(g.texX, g.texY);glVertex2f(x + dx + left, y + dy +  g.bitmap_top +top); //top left
					glTexCoord2f(g.texX + g.texW, g.texY);glVertex2f(x + dx + left + g.realW, y + dy + g.bitmap_top + top); //top right
					glTexCoord2f(g.texX + g.texW, g.texY +g.texH);glVertex2f(x + dx + left + g.realW,y + dy + top + g.bitmap_top + g.realH); // bottom right
					glTexCoord2f(g.texX, g.texY +g.texH);glVertex2f(x + dx + left, y + dy + top + g.bitmap_top + g.realH); //bottom left
				glEnd();
				left += g.realW;
			}
		}
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
	
	Text* Text::setOutline(float out, float red, float green, float blue, float alpha)
	{
		outline = out;
		outlineColor[0] = red;
		outlineColor[1] = green;
		outlineColor[2] = blue;
		outlineColor[3] = alpha;
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
	    setFont("../fonts/Ubuntu-m.ttf",33); //такое вот умолчание
		shadowDx = shadowDy = 0.0;
		kerning = false;
		changed = true;
		color[0] = 0.;
		color[1] = 0.;
		color[2] = 0.;
		color[3] = 1.;
		outline = 0.0;
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