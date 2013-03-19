#include "Background.h"
#include "Graphics.h"
#include "defs.h"
#include <iostream>
Background::Background()
{
	texX = 0;
	dx = 0;
	y = 0;
}


Background* Background::setX(float x)
{
	dx = x;
	return this;
}

Background* Background::setY(float y_)
{
	y = y_;
	return this;
}

Background* Background::draw()
{
	texX += dx;
	if(texX < 0) texX += 1.0;
	if(texX > 1) texX -= 1.0;
	glEnable (GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		  glTexCoord2f(0.0+texX, 0.0f);glVertex2f(0, y); //top left
		  glTexCoord2f(1.0+texX, 0.0);glVertex2f(texWidth, y); //top right
		  glTexCoord2f(1.0f+texX, 1.0f);glVertex2f(texWidth, texHeight+y); // bottom right
		  glTexCoord2f(0.0+texX, 1.0f);glVertex2f(0, texHeight+y); //bottom left
		glEnd();		
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	return this;
}

Background* Background::setTexture(char* file)
{
	texture = Graphics::png2tex(file);
	texWidth = Graphics::retWidth;
	texHeight = Graphics::retHeight;
	return this;
}