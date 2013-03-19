<<<<<<< HEAD

=======
#include <GL\glu.h>
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
#include "Graphics.h"
#include "defs.h"
#include "lodepng.h"

<<<<<<< HEAD
unsigned Graphics::retWidth, Graphics::retHeight;
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
void Graphics::color(float R,float G,float B)
{
	glColor3f(R,G,B);
}

<<<<<<< HEAD
void Graphics::color(Color4f c)
{
	glColor4f(c.red,c.green,c.blue,c.alpha);
}

=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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
<<<<<<< HEAD
	glBegin(GL_QUADS);
=======
	glBegin(GL_LINE_LOOP);
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
		glVertex2f(X,Y);
		glVertex2f(X+W,Y);
		glVertex2f(X+W,Y+H);
		glVertex2f(X,Y+H);
	glEnd();
}

<<<<<<< HEAD
void Graphics::roundedRectangle(float X,float Y,float W,float H, float R)
{
	if (R == 0)
	{
		rectangle(X, Y, W, H);
		return;
	}
	glBegin(GL_TRIANGLE_FAN);

		glVertex2f(X + W/2,Y + H/2);//center
		glVertex2f(X, Y + H - R);
		for(int i = 180; i < 270; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + R,sin(a)*R + Y + R);
		}
		for(int i = 270; i < 360; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + W - R,sin(a)*R + Y + R);
		}
		for(int i = 0; i < 90; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + W - R,sin(a)*R + Y + H - R);
		}
		for(int i = 90; i < 180; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + R,sin(a)*R + Y + H - R);
		}
		glVertex2f(X, Y + H - R);
	glEnd();
}

void Graphics::roundedRectangle(float X,float Y,float W,float H, float R,Color4f c1,Color4f c2)
{
	if (R == 0)
	{
		rectangle(X, Y, W, H);
		return;
	}
	glBegin(GL_TRIANGLE_FAN);
		//glVertex2f(X + W/2,Y + H/2);//center
		color(c2);
		glVertex2f(X, Y + H - R);
		color(c1);
		for(int i = 180; i < 270; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + R,sin(a)*R + Y + R);
		}
		for(int i = 270; i < 360; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + W - R,sin(a)*R + Y + R);
		}
		color(c2);
		for(int i = 0; i < 90; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + W - R,sin(a)*R + Y + H - R);
		}
		for(int i = 90; i < 180; i += 5)
		{
			float a = radian(i);
			glVertex2f(cos(a)*R + X + R,sin(a)*R + Y + H - R);
		}
		glVertex2f(X, Y + H - R);
	glEnd();
}

=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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
<<<<<<< HEAD
	unsigned texture;
	lodepng_decode32_file(&data, &retWidth, &retHeight, name);
=======
	unsigned width, height;
	unsigned texture;
	lodepng_decode32_file(&data, &width, &height, name);
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
<<<<<<< HEAD
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, retWidth, retHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
=======
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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

<<<<<<< HEAD


=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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