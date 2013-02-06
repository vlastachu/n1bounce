#include "GraphicShape.h"
#include "defs.h"
#include <math.h>

GraphicShape::GraphicShape(){}
GraphicShape::~GraphicShape(){}

float GraphicShape::radian(float a) {
	return a / 180 * PI;
}

void GraphicShape::circle(int X, int Y, int R)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<360;i+=5)
	{
		float a = radian(i);
		glVertex2f(cos(a)*R+X,sin(a)*R+Y);
	}
	glEnd();
}

float GraphicShape::getx()
{
	return x;
}

float GraphicShape::gety()
{
	return y;
}
