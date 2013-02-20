#pragma once

class Graphics
{
	static float radian(float a);
public:
	static unsigned retWidth, retHeight;
	static unsigned png2tex(const char* name);
	static void draw(float X,float Y,float W,float H,float Rot,unsigned Texture);
	static void draw(float X,float Y,float W,float H,unsigned Texture);
	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
	static void color(float R,float G,float B);
	static void line(float X1,float Y1,float X2,float Y2);
};