#include "Ninja.h"
#include "Engine.h"
	
Ninja::Ninja(GameCore* Parent)
{
	parent=Parent;
	
	//body.texture=Graphics::png2tex("../data/ninja.png");
	//leg1.texture=Graphics::png2tex("../data/leg.png");
	//leg2.texture=leg1.texture;
	//katana.texture=Graphics::png2tex("../data/katana.png");
}

void Ninja::init()
{	
	
	x=parent->xScaleAxis;
	y=HEIGHT*0.8;
	r=HEIGHT*0.05;
	phase=0;
	state=1;
	dy      = 0;
	jmp     = 0;
	impulse = 15;


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
	
	Graphics::draw(0,0,1,1, parent->toX(leg1.x+x)   , parent->toY(leg1.y+y)   , parent->toL(leg1.w)   , parent->toL(leg1.h)   ,0.5,0.5,   leg1.rot   , "n_leg");
	Graphics::draw(0,0,1,1, parent->toX(body.x+x)   , parent->toY(body.y+y)   , parent->toL(body.w)   , parent->toL(body.h)   ,0.5,0.5,   body.rot   , "n_body");
	Graphics::draw(0,0,1,1, parent->toX(katana.x+x) , parent->toY(katana.y+y) , parent->toL(katana.w) , parent->toL(katana.h) ,0.5,0.5, katana.rot   , "n_katana");
	Graphics::draw(0,0,1,1, parent->toX(leg2.x+x)   , parent->toY(leg2.y+y)   , parent->toL(leg2.w)   , parent->toL(leg2.h)   ,0.5,0.5,   leg2.rot   , "n_leg");
}

void Ninja::move()
{
	if(y >= HEIGHT*2) //TODO: NICER!!
	{
		parent->gameOver("deadline");
	}

	prevY=y;
	y -= r*dy*0.07f;//def
	dy--;
	
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
		if(state!=3 && state!=5)
		{
			state=2;
			if(jmp==0)
				jmp=1;
		}
	}
	

	if(phase>=1)
		phase=0;
	switch(state)
	{
	case 1:
		h=r*4;

		body.x=0;
		body.y=static_cast<float>((-abs(sin(2*PI*(phase+0.25)))-1) * r*2);
		body.rot=30;
		
		leg1.x=static_cast<float>(cos(2*PI*phase)*r*3/2 - r/2);
		leg1.y=static_cast<float>(sin(2*PI*phase)*r - r*5/4);
		leg1.rot=0;

		leg2.x=static_cast<float>(cos(2*PI*(phase+0.5))*r*3/2 - r/2);
		leg2.y=static_cast<float>(sin(2*PI*(phase+0.5))*r - r*5/4);
		leg2.rot=0;

		katana.x=-r*2/4;
		katana.y=static_cast<float>((-abs(sin(2*PI*(phase+0.25)))-0.8)*r*2);
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


		leg1.x=static_cast<float>(cos(2*PI*(phase+0.25))*r*1.2);
		leg1.y=static_cast<float>(sin(2*PI*(phase+0.25))*r*1.2 - r*2);
		leg1.rot=phase*360;

		leg2.x=static_cast<float>(cos(2*PI*(phase+0.30))*r*1.2);
		leg2.y=static_cast<float>(sin(2*PI*(phase+0.30))*r*1.2 - r*2);
		leg2.rot=(phase+0.1f)*360;//f
		
		katana.x=static_cast<float>(cos(2*PI*phase-0.7)*r);
		katana.y=static_cast<float>(-r*2+sin(2*PI*phase-0.7)*r);
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
		leg1.x=-r*2.5f;//f
		leg1.rot=0;

		leg2.y=-r*0.7f;//f
		leg2.x=-r*2.8f;//f
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
		body.x-=parent->speed;
		phase+=(float)1/20;
		if(phase>=1)
			parent->gameOver("trap");
		break;
	}
}

void Ninja::jump()
{
	if(jmp < 2 && state!=5)
	{
		if(jmp==1)
		{
			setState(3);
		}
		dy=impulse;
		jmp++;
	}
}

void Ninja::slide()
{
	if(state!=5)
		setState(4);
}