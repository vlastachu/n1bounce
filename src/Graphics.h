#pragma once
//#include "lodepng.h"

class Graphics
{
	static float radian(float a);
public:
	static unsigned png2tex(const char* name);
	static void draw(float X,float Y,float W,float H,float Rot,unsigned Texture);
	static void circle(int X, int Y, int R);
};