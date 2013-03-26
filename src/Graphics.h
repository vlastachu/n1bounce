#pragma once
#include <map>
#include <string>
using std::string;
using std::map;
#include <ft2build.h>
#include FT_FREETYPE_H

class FreeTypeHelper
{
private:
	FreeTypeHelper();
	FT_Library ft;
public:
	static FT_Library getLib();
};
struct Color4f
{
	float red,green, blue, alpha;
	Color4f(float r, float g, float b, float a):red(r),green(g),blue(b),alpha(a){}
	Color4f():red(0),green(0),blue(0),alpha(0){}
};

class TextStyle{
private:

public:
	const float shadowDx, shadowDy, outline;
	const Color4f color, shadowColor, outlineColor;
	TextStyle():shadowDx(0),shadowDy(0), outline(0),color(Color4f()), shadowColor(Color4f()), outlineColor(Color4f()){}
	TextStyle(float shadowDx, float shadowDy, float outline,Color4f color, Color4f shadowColor, Color4f outlineColor):
		shadowDx(shadowDx),shadowDy(shadowDy), outline(outline),color(color), shadowColor(shadowColor), outlineColor(outlineColor){}
};

struct Gradient{  //лично мне уже не нужен. TODO: del
	Color4f color1;
	Color4f color2;
	Gradient(){}
	Gradient(Color4f c1,Color4f c2):color1(c1),color2(c2){}
};


class Background
{
private:
	float dx, y, texX;
	//unsigned texWidth, texHeight;  //nu hz 
	string texture;
public:
	Background* draw();
	Background(char* file, float y, float dx);
};

//struct GlyphCash{
//		float texX, texY, texW,texH,realW,realH;
//
//		int bitmap_left;
//		int bitmap_top;
//		GlyphCash(float x, float y, float w, float h,float rw, float rh, int left, int top):
//			texX(x),texY(y), texW(w),texH(h),realW(rw),realH(rh),bitmap_left(left),bitmap_top(top){}
//		GlyphCash(){}
//	};


//struct Font
//{
//	unsigned texture;
//	int xNum,yNum,startChar;
//	Font(unsigned Texture,int XNum,int YNum,int StartChar)
//	{
//		xNum=XNum;yNum=YNum;startChar=StartChar;texture=Texture;
//	};
//};

class Graphics
{
	//static std::map<char, GlyphCash> glyphCash;
	static map<string,unsigned> textures;
	static const unsigned fontSize = 64, fontTexColumns = 16, fontTexRows = 16; 
	static float radian(float a);
	static void outCharXY(float X,float Y,float W,float H,char C,unsigned tex);

public:
	
	static void addFont(string FontName);

	static void outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName);
	static void outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName,TextStyle style);
	static void addTexture(unsigned TextureId,string TextureName);

	static unsigned ttf2tex(string tex);
	static unsigned png2tex(const char* name);
	static unsigned png2tex(const char* name, unsigned &width, unsigned &height);
	static void draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture);
	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
	static void roundedRectangle(float X,float Y,float W,float H,float radius);
	static void color(float R,float G,float B);
	static void color(Color4f c);
	static void line(float X1,float Y1,float X2,float Y2);
	static float getWindowHeight();
	static float getWindowWidth();
};