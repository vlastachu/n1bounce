
#include "Ninja.h"
//#include "defs.h"
//#include <iostream>
//using namespace std;

	
Ninja::Ninja(GameCore* Parent)
{
	parent=Parent;
	
	body.texture=Graphics::png2tex("../image/ninja.png");
	leg1.texture=Graphics::png2tex("../image/leg.png");
	leg2.texture=leg1.texture;
	katana.texture=Graphics::png2tex("../image/katana.png");
}

void Ninja::init()
{	
	
	x=XSCALE_AXIS;
	y=200;
	r=15;
	phase=0;
	state=1;
	dy      = 0;
	jmp     = 0;
	impulse = 16;

	body.w=r*2;
	body.h=r*2;

	leg1.w=r;
	leg1.h=r/2;

	leg2.w=r;
	leg2.h=r/2;

	katana.w=r*4;
	katana.h=r/2;
}

void Ninja::draw()
{
	//Graphics::circle(x,y-r,r);
	
	Graphics::draw(parent->toX(leg1.x+x)   , parent->toY(leg1.y+y)   , parent->toL(leg1.w)   , parent->toL(leg1.h)   , leg1.rot   , leg1.texture);
	Graphics::draw(parent->toX(body.x+x)   , parent->toY(body.y+y)   , parent->toL(body.w)   , parent->toL(body.h)   , body.rot   , body.texture);
	Graphics::draw(parent->toX(katana.x+x) , parent->toY(katana.y+y) , parent->toL(katana.w) , parent->toL(katana.h) , katana.rot , katana.texture);
	Graphics::draw(parent->toX(leg2.x+x)   , parent->toY(leg2.y+y)   , parent->toL(leg2.w)   , parent->toL(leg2.h)   , leg2.rot   , leg2.texture);
}

void Ninja::move()
{
	if(y >= HEIGHT*2)
	{
		parent->gameOver("deadline");
	}

	prevY=y;
	y -= dy;
	dy--;
	
	/*if(state==1)
	{
		state=2;
	}*/
	if(prevY<=borderY && y>=borderY)
	{
		dy=0;
		jmp=0;
		y=borderY;
		if(state!=4 && state!=5)
			state=1;
	}
	else
	{
		if(state==1 || state==4)
			jmp=1;

		if(state!=3 && state!=5)
		{
			state=2;
		}
	}
	

	if(phase>=1)
		phase=0;
	switch(state)
	{
	case 1:
		h=r*4;

		body.x=0;
		body.y=(-abs(sin(2*PI*(phase+0.25)))-1) * r*2;
		body.rot=30;
		
		leg1.x=cos(2*PI*phase)*r*3/2 - r/2;
		leg1.y=sin(2*PI*phase)*r - r*5/4;
		leg1.rot=0;

		leg2.x=cos(2*PI*(phase+0.5))*r*3/2 - r/2;
		leg2.y=sin(2*PI*(phase+0.5))*r - r*5/4;
		leg2.rot=0;

		katana.x=-r*2/4;
		katana.y=(-abs(sin(2*PI*(phase+0.25)))-0.8)*r*2;
		katana.rot=30;

		phase+=(float)1/20;
		break;
	case 2:
		h=r*5;

		body.x=0;
		body.y=-r*4;
		body.rot=-30;

		leg1.x= -r;
		leg1.y=	-r/4;
		leg1.rot=0;

		leg2.x= -r*3/2;
		leg2.y= -r;
		leg2.rot=0;

		katana.x=r/2;
		katana.y=-r*2;
		katana.rot=-80;
		
		break;
	case 3:
		h=r*3;

		body.x=0;
		body.y=-r*2;
		body.rot=phase*360;


		leg1.x=cos(2*PI*(phase+0.25))*r*1.2;
		leg1.y=sin(2*PI*(phase+0.25))*r*1.2 - r*2;
		leg1.rot=phase*360;

		leg2.x=cos(2*PI*(phase+0.30))*r*1.2;
		leg2.y=sin(2*PI*(phase+0.30))*r*1.2 - r*2;
		leg2.rot=(phase+0.1)*360;
		
		katana.x=cos(2*PI*phase-0.7)*r;
		katana.y=-r*2+sin(2*PI*phase-0.7)*r;
		katana.rot=phase*360+90;

		phase+=(float)1/10;
		if(phase>=1)
			state=2;

		break;
	case 4:
		h=r*2;

		body.x=0;
		body.y=-r;
		body.rot=0;

		leg1.y=-r;
		leg1.x=-r*2.5;
		leg1.rot=0;

		leg2.y=-r*0.7;
		leg2.x=-r*2.8;
		leg2.rot=0;

		katana.x=r*2;
		katana.y=-r*3/4;
		katana.rot=180;
		
		phase+=(float)1/20;
		if(phase>=1)
			state=1;
		break;
	case 5:
		h=0;

		parent->gameOver("trap");
		break;
	}
}

void Ninja::jump()
{
	if(jmp < 2)
	{
		//air=true;
		if(jmp==1)
		{
			phase=0;
			state=3;
		}
		dy=impulse;
		jmp++;
	}
}

void Ninja::slide()
{
	setState(4);
}