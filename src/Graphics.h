#pragma once
#include <map>
#include <string>
#define string std::string
#define map std::map

struct Font
{
	unsigned texture;
	int xNum,yNum,startChar;
	Font(unsigned Texture,int XNum,int YNum,int StartChar)
	{
		xNum=XNum;yNum=YNum;startChar=StartChar;texture=Texture;
	};
};

class Graphics
{
	static map<string,unsigned> textures;
	static map<string,Font> fonts;

	static float radian(float a);
	static void outCharXY(float X,float Y,float W,float H,char C,string FontName);

public:
	static void addTexture(unsigned TextureId,string TextureName);
	static void addFont(unsigned TextureId,int XNum,int YNum,int StartChar,string FontName);

	static void outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName);

	static unsigned png2tex(const char* name);
	static void draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture);

	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
	static void color(float R,float G,float B);
	static void line(float X1,float Y1,float X2,float Y2);
};