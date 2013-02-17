
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
	
	x=200;
	y=200;
	r=15;
	phase=0;
	state=1;
	dy      = 0;
	jmp     = false;
	impulse = 16;
	air=true;

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
	Graphics::draw(leg1.x+x, leg1.y+y, leg1.w, leg1.h, leg1.rot, leg1.texture);
	Graphics::draw(body.x+x, body.y+y, body.w, body.h, body.rot, body.texture);
	Graphics::draw(katana.x+x, katana.y+y, katana.w, katana.h, katana.rot, katana.texture);
	Graphics::draw(leg2.x+x, leg2.y+y, leg2.w, leg2.h, leg2.rot, leg2.texture);
}

void Ninja::move()
{
	prevY=y;
	//state=2;
	y -= dy;
	dy--;
	if(state!=3)
	{
		state=2;
	}
	if(prevY<=borderY && y>=borderY)
	{
		dy=0;
		jmp=0;
		y=borderY;
		state=1;
	}
	

	if(phase>=1)
		phase=0;
	switch(state)
	{
	case 1:
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

		phase+=(float)1/15;
		if(phase>=1)
			state=2;

		break;
	case 4:
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