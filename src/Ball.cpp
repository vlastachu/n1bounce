#include "defs.h"
#include "Ball.h"
#include "GraphicShape.h"

Ball::Ball()
{
	x       = BALLX;
	y       = 500;

}

void Ball::setborder(float Y)
{
	yborder = Y - r;
}

void Ball::init()
{
	r       = 20;
	dy      = 0;
	jmp     = false;
	impulse = 20;
	setborder(500);
}

void Ball::jump()
{
	if(!jmp)
	{
		dy=impulse;
		jmp=true;
	}
}

void Ball::move()
{
	if(jmp)
	{
		y -= dy;
		dy--;
		if(y > yborder)
		{
			y   = yborder;
			dy  = 0;
			jmp = false;
		}	
	}
}

void Ball::draw()
{
	glColor3f (1.0,0.0,0.0);
	circle (x,y,r);
}