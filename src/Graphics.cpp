#include <GL\glu.h>
#include "defs.h"
#include "lodepng.h"
#include "Graphics.h"
#include <GL/glut.h>
#include <iostream>
#include <ft2build.h>
Background::Background(char* file, float Y, float Dx)
{
	texX = 0;
	dx = Dx;
	y = Y;
	texture = file;
}

FreeTypeHelper::FreeTypeHelper(){
	if (FT_Init_FreeType(&ft)) {
			fprintf(stderr, "Could not init freetype library\n");
			return;
	}
}

FT_Library FreeTypeHelper::getLib()
{
        static FreeTypeHelper instance;
        return instance.ft;
}

Background* Background::draw()
{
	texX += dx;
	if(texX < 0) texX += 1.0;
	if(texX > 1) texX -= 1.0;
	//Graphics::draw(texX,0.0,1.0+texX,1.0, 0, y,texWidth,texHeight, 0, 0, 0, texture);  
	/*
	ne katit. ne znayu shirini i visoti, ne mogu skazat repeat
	*/
	return this;
}


void Graphics::color(float R,float G,float B)
{
	glColor3f(R,G,B);
}

void Graphics::color(Color4f c)
{
	glColor4f(c.red,c.green,c.blue,c.alpha);
}

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
	return a / 180 * PI;
}
unsigned Graphics::png2tex(const char* name)
{
	unsigned width, height;
	return png2tex(name, width, height);
}

unsigned Graphics::png2tex(const char* name, unsigned &width, unsigned &height)
{
	unsigned char* data;
	unsigned texture;
	if(!lodepng_decode32_file(&data, &width, &height, name))
	{
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
	}
	else{
		std::cerr << "texture load error. name: " << name << "\n";
		return 0;
	}
	return texture;
}

unsigned Graphics::ttf2tex(string tex)
{
	FT_Library ft = FreeTypeHelper::getLib();
	FT_Face face;
	if (FT_New_Face(ft, tex.c_str(), 0, &face)) {
		fprintf(stderr, "Could not open font %s\n", tex);
		return 0;
	}	
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	unsigned char *data = new unsigned char[fontSize*fontSize*fontTexColumns*fontTexRows];
	for(unsigned int i = 0; i < fontSize*fontSize*fontTexColumns*fontTexRows;i++) data[i] = 0;
	int left = 0, top = 0; 
	for(unsigned int k = 0; k < fontTexRows; k++){
		for(unsigned int i = 0; i < fontTexColumns; i++){	
		FT_Load_Char( face, (char)(k*fontTexColumns + i), FT_LOAD_RENDER ); 
			int pitch = face->glyph->bitmap.pitch;
			if (pitch < 0) pitch = -pitch;
			for (int row = 0; row < face->glyph->bitmap.rows; ++row) 
				std::memcpy(data + left + fontTexColumns*fontSize*(row + top)
					, face->glyph->bitmap.buffer + pitch * row, pitch);
			left += fontSize;
		}
		top += fontSize;
		left = 0;
	}
	//fontSize-face->glyph->bitmap_top
	GLuint texture;
	glGenTextures(1,&texture);
	addTexture(texture, tex);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, fontSize*fontTexColumns, fontSize*fontTexRows, GL_ALPHA, GL_UNSIGNED_BYTE, data);
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

map<string,unsigned> Graphics::textures;

void Graphics::addTexture(unsigned TextureId,string TextureName)
{
	textures.insert(std::pair<string,unsigned>(TextureName,TextureId));
}





float Graphics::getWindowHeight(){
	return glutGet(GLUT_WINDOW_WIDTH);
}

float Graphics::getWindowWidth(){
	return glutGet(GLUT_WINDOW_HEIGHT);
}

void Graphics::outCharXY(float X,float Y,float W,float H,char C, unsigned tex)
{
	float x1=C%fontTexColumns/(float)fontTexColumns;
	float y1=C/fontTexColumns/(float)fontTexRows;
	float x2=x1+1/(float)fontTexColumns;
	float y2=y1+1/(float)fontTexRows;
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	color(Color4f(1,0,1,1));
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glBindTexture( GL_TEXTURE_2D, tex);
	glBegin( GL_QUADS );
		glTexCoord2f(x1,y1); glVertex2f(X,Y);
		glTexCoord2f(x1,y2); glVertex2f(X,Y+H);
		glTexCoord2f(x2,y2); glVertex2f(X+W,Y+H);
		glTexCoord2f(x2,y1); glVertex2f(X+W,Y);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void Graphics::outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName)
{
	map<string,unsigned>::iterator it=textures.find(FontName);
	if(it==textures.end()) return;

	for(int i=0;Str[i]!='\0';i++)
		outCharXY(X+CharW*i,Y,CharW,CharH,Str[i], it->second);
}


void Graphics::outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName,TextStyle style)
{
	if(style.shadowDx != 0.0 && style.shadowDy != 0.0){
		color(style.shadowColor);
		outTextXY(X + style.shadowDx,Y + style.shadowDy, CharW, CharH,Str,FontName);
	}
	if(style.outline != 0.0){
		color(style.outlineColor);
		float detalization = 4*style.outline*style.outline;
		float Dx, Dy;
		for(float i = 0.0; i <= PI*2; i += PI*2/detalization)
		{
			Dx = style.outline*cos(i), Dy = style.outline*sin(i);
			outTextXY(X + Dx,Y + Dy, CharW, CharH,Str,FontName);
		}
	}
	color(style.color);
	outTextXY(X,Y, CharW, CharH,Str,FontName);
}

void Graphics::addFont(string FontName)
{
	string ext = FontName.substr(FontName.size()-3,3);
	if(ext == "png")
		textures.insert(std::pair<string,unsigned>(FontName,png2tex(FontName.c_str())));
	else if(ext == "ttf" || ext == "otf")
		textures.insert(std::pair<string,unsigned>(FontName,ttf2tex(FontName)));
}