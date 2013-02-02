#include "defs.h"
#include "Platform.h"
void Platform::draw()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		glVertex2f(x+w,y+h);
		glVertex2f(x,y+h);
	glEnd();
}
Platform::Platform()
{
	x=WIDTH;
	y=500;
	w=100;
	h=30;
}
Platform::Platform(int height, int width)
{
	x=WIDTH;
	y=HEIGHT-height;
	w=width;
	h=30;
}