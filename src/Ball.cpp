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
	x       = BALLX;
	y       = 500;
	r       = 20;
	dy      = 0;
	jmp     = false;
	impulse = 16;
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
	if(!(y >= yborder && y < yborder + 10) || jmp) //����� ����� ���� ����� ������� �� ���������
	{
		y -= dy;
		dy--;
	}
	if(y >= yborder && y < yborder + 10)
	{
			y   = yborder;
			dy  = 0;
			jmp = false;
	}
}

void Ball::draw()
{
	glColor3f (1.0,0.0,0.0);
	circle (x,y,r);
}