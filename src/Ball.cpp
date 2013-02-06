#include "defs.h"
#include "Ball.h"
#include "GraphicShape.h"

Ball::Ball()
{
	x       = BALLX;
	y       = 500;

}

void Ball::keyPressed(unsigned char key)
{
	if(key=='w')
	{
		jump();
	}
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
	if(jmp < 2)
	{
		dy=impulse;
		jmp++;
	}
}

void Ball::move()
{
	if(!(y >= yborder && y < yborder + 10) || jmp) //чтобы можно было сбоку заехать на платформу
	{
		y -= dy;
		dy--;
	}
	if(y >= yborder + dy && y < yborder + 10)
	{
			y   = yborder;
			dy  = 0;
			jmp = 0;
	}
}

void Ball::draw()
{
	glColor3f (1.0,0.0,0.0);
	circle (x,y,r);
}