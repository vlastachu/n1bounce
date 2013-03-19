#pragma once

<<<<<<< HEAD

struct Color4f
{
	float red,green, blue, alpha;
	Color4f(float r, float g, float b, float a):red(r),green(g),blue(b),alpha(a){}
	Color4f(){Color4f(0, 0, 0, 0);}
};
struct Gradient{
	Color4f color1;
	Color4f color2;
	Gradient(){}
	Gradient(Color4f c1,Color4f c2):color1(c1),color2(c2){}
};

=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
class Graphics
{
	static float radian(float a);
public:
<<<<<<< HEAD
	static unsigned retWidth, retHeight;
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
	static unsigned png2tex(const char* name);
	static void draw(float X,float Y,float W,float H,float Rot,unsigned Texture);
	static void draw(float X,float Y,float W,float H,unsigned Texture);
	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
<<<<<<< HEAD
	static void roundedRectangle(float X,float Y,float W,float H,float radius);
	static void roundedRectangle(float X,float Y,float W,float H,float radius,Color4f c1,Color4f c2);
	static void color(float R,float G,float B);
	static void color(Color4f c);
=======
	static void color(float R,float G,float B);
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
	static void line(float X1,float Y1,float X2,float Y2);
};