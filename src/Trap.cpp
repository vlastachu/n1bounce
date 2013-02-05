#include "defs.h"
#include "Trap.h"
void Trap::draw()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
		glVertex2f(x+w,y);
		glVertex2f(x+(w/2),y-h);
	glEnd();
}

Trap::Trap(int Y, int X)
{
	u=0;
	x=X;
	y=HEIGHT-Y;
	w=30;
	h=30;
}


ClassType Trap::getType(){
	return trap;
}