
#include <GL/glew.h>
#include <GL\glu.h>
#include "Graphics.h"
#include "defs.h"
#include "lodepng.h"

unsigned Graphics::retWidth, Graphics::retHeight;
void Graphics::color(float R,float G,float B)
{
	glColor3f(R,G,B);
}

void Graphics::circle(float X, float Y, float R)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<360;i+=5)
	{
		float a = radian(i);
		glVertex2f(cos(a)*R+X,sin(a)*R+Y);
	}
	glEnd();
}

void Graphics::rectangle(float X,float Y,float W,float H)
{
	glBegin(GL_QUADS);
		glVertex2f(X,Y);
		glVertex2f(X+W,Y);
		glVertex2f(X+W,Y+H);
		glVertex2f(X,Y+H);
	glEnd();
}

void Graphics::line(float X1,float Y1,float X2,float Y2)
{
	glBegin(GL_LINE);
		glVertex2f(X1,Y1);
		glVertex2f(X2,Y2);
	glEnd();
}

float Graphics::radian(float a)
{
	return a / 180 * PI;
}
unsigned Graphics::png2tex(const char* name)
{
	unsigned char* data;
	unsigned texture;
	lodepng_decode32_file(&data, &retWidth, &retHeight, name);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, retWidth, retHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	delete data;
	return texture;
}
void Graphics::draw(float X,float Y,float W,float H,float Rot,unsigned Texture)
{
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, Texture);

	glPushMatrix();

	glRotatef(Rot, 0, 0, 1);
	glTranslatef((X)*cos(radian(Rot)) + (Y)*sin(radian(Rot)),
					(Y)*cos(radian(Rot)) - (X)*sin(radian(Rot)), 0);

	glColor3f(1.0,1.0,1.0);
	glBegin( GL_QUADS );
		glTexCoord2f(0,0); glVertex2f(-W/2,-H/2);
		glTexCoord2f(0,1); glVertex2f(-W/2,H/2);
		glTexCoord2f(1,1); glVertex2f(W/2,H/2);
		glTexCoord2f(1,0); glVertex2f(W/2,-H/2);
	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Graphics::draw(float X,float Y,float W,float H,unsigned Texture)
{
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, Texture);

	glColor3f(1.0,1.0,1.0);
	glBegin( GL_QUADS );
		glTexCoord2f(0,0); glVertex2f(X,Y);
		glTexCoord2f(0,1); glVertex2f(X,Y+H);
		glTexCoord2f(1,1); glVertex2f(X+W,Y+H);
		glTexCoord2f(1,0); glVertex2f(X+W,Y);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}