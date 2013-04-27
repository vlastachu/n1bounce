#include "defs.h"
#include <GL/glu.h>
#include "lodepng.h"
#include "Graphics.h"

void Graphics::color(float R,float G,float B)
{
	glColor3f(R,G,B);
}

void Graphics::circle(float X, float Y, float R)
{
	glBegin(GL_LINE_LOOP);
	for(float i=0;i<360;i+=5)
	{
		float a = radian(i);
		glVertex2f(cos(a)*R+X,sin(a)*R+Y);
	}
	glEnd();
}

void Graphics::rectangle(float X,float Y,float W,float H)
{
	glBegin(GL_LINE_LOOP);
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
	return static_cast<float>(a / 180 * PI);
}
unsigned Graphics::png2tex(const char* name)
{
	unsigned char* data;
	unsigned width, height;
	unsigned texture;
	lodepng_decode32_file(&data, &width, &height, name);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	delete data;
	return texture;
}
void Graphics::draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture)
{
	map<string,unsigned>::iterator it=textures.find(Texture);
	if(it==textures.end()) return;
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, it->second);

	glPushMatrix();

	glRotatef(Rot, 0, 0, 1);
	glTranslatef((X)*cos(radian(Rot)) + (Y)*sin(radian(Rot)),
					(Y)*cos(radian(Rot)) - (X)*sin(radian(Rot)), 0);

	glColor3f(1.0,1.0,1.0);
	glBegin( GL_QUADS );
		glTexCoord2f(X1,Y1); glVertex2f(W*-X0,H*-Y0);
		glTexCoord2f(X1,Y2); glVertex2f(W*-X0,H*(1-Y0));
		glTexCoord2f(X2,Y2); glVertex2f(W*(1-X0),H*(1-Y0));
		glTexCoord2f(X2,Y1); glVertex2f(W*(1-X0),H*-Y0);
	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

map<string,Font> Graphics::fonts;
map<string,unsigned> Graphics::textures;

void Graphics::addTexture(unsigned TextureId,string TextureName)
{
	textures.insert(std::pair<string,unsigned>(TextureName,TextureId));
}

void Graphics::outCharXY(float X,float Y,float W,float H,char C,string FontName)
{
	map<string,Font>::iterator it=fonts.find(FontName);
	if(it==fonts.end()) return;
	float x1=((C-it->second.startChar)%it->second.xNum)/(float)it->second.xNum;
	float y1=((C-it->second.startChar)/it->second.xNum)/(float)it->second.yNum;
	float x2=x1+1/(float)it->second.xNum;
	float y2=y1+1/(float)it->second.yNum;

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, it->second.texture);

	glColor3f(1.0,1.0,1.0);
	glBegin( GL_QUADS );
		glTexCoord2f(x1,y1); glVertex2f(X,Y);
		glTexCoord2f(x1,y2); glVertex2f(X,Y+H);
		glTexCoord2f(x2,y2); glVertex2f(X+W,Y+H);
		glTexCoord2f(x2,y1); glVertex2f(X+W,Y);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//draw(x1,y1,x2,y2,X,Y,W,H,0,0,0,it->second.texture);
}

void Graphics::outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName)
{
	for(int i=0;Str[i]!='\0';i++)
		outCharXY(X+CharW*i,Y,CharW,CharH,Str[i],FontName);
}

void Graphics::addFont(unsigned TextureId,int XNum,int YNum,int StartChar,string FontName)
{
	fonts.insert(std::pair<string,Font>(FontName,Font(TextureId,XNum,YNum,StartChar)));
}
























