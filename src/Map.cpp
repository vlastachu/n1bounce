#include "Map.h"
#include "Engine.h"
#include <iostream>

Map::Map(GameCore* Root)
{
	root=Root;
}

void Map::draw()
{
	
	for(std::list<MapShape*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->draw();
	
	}
}

void Map::init()
{
	for(std::list<MapShape*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		delete *it;
	}
	elements.clear();

	Platform* p=new Platform(-HEIGHT*0.2,HEIGHT*0.8,WIDTH,root);       //    UNSAFE NULL->x   //def
	elements.push_back(p);
	lastPlat=p;
	archBoss=NULL;//kostil
}


Platform* Map::addPlatform()
{
	float deltaY=rand()%int(HEIGHT*0.5);  //def
	float directionY=rand()%2;
	if(directionY==0) directionY=-1;
	if(lastPlat->y+deltaY>HEIGHT*0.9)  //def
	{
		directionY=-1;
	}
	else if(lastPlat->y-deltaY<HEIGHT*0.1)  //def
	{
		directionY=1;
	}
		
	Platform* p=new Platform(lastPlat->x+lastPlat->w+HEIGHT/2,lastPlat->y+directionY*deltaY,HEIGHT/2+rand()%int(HEIGHT),root);  //def
	lastPlat=p;  //										|										|
	elements.push_back(p);  //							<--------------different---------------->
	return p;
}
void Map::move()
{
	if(archBoss)
	{

	}


	if(root->toX(lastPlat->x + lastPlat->w + HEIGHT/2) <= WIDTH)  //def
	{
		Platform* p=addPlatform();//TODO: fix
		if(!(rand()%4))
		{
			elements.push_back(p->addTrap());
		}
		else if(p->w>HEIGHT)   //def
		{
			elements.push_back(p->addDB());
		}
		else
		{
			if(!archBoss)
			{
				std::list<Platform*> _platforms;
				for(int i=0;i<4;i++)
				{
					_platforms.push_back(addPlatform());
					std::cout<<_platforms.back()->x<<"\n";
				}
				archBoss=_platforms.back()->addArcher();
				elements.push_back(archBoss);
				for(std::list<Platform*>::iterator it = _platforms.begin(); it != _platforms.end(); it++)
				{
					archBoss->addTarget(new Point((*it)->x,(*it)->y));
					elements.push_back(archBoss->shoot());
				}
			}
			
			//elements.push_back(archer->shoot());
		}
	}

	if(!elements.empty())
	{
		if((elements.front()->x + elements.front()->w) < - WIDTH)  //TODO: do it nicer
		{
			delete *elements.begin();
			elements.erase(elements.begin());
		}
	}


	root->getNinja()->setBorder(HEIGHT);  //TODO: do it nicer
	for(std::list<MapShape*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		//(*it)->x-=root->speed;
		(*it)->move();
	}
	
}




//____MapShape_________________________________________________________________________________________________




MapShape::MapShape(float X,float Y,float W,float H,GameCore* Root)
{
	x=X;y=Y;w=W;h=H;root=Root;
}

Trap::Trap(float X,float Y,GameCore* Root):MapShape(X,Y,HEIGHT*0.1,HEIGHT*0.05,Root)  //def
{
}

void Trap::draw()
{
	Graphics::color(1,0,0);
	Graphics::rectangle(root->toX(x),root->toY(y),root->toL(w),root->toL(h));
}

void Trap::move()
{
	x-=root->speed;
	if(x<root->getNinja()->x && x+w>root->getNinja()->x && y<=root->getNinja()->y && y+h>=root->getNinja()->y)
	{
		root->getNinja()->setState(5);
	}
}


Platform::Platform(float X,float Y,float W,GameCore* Root):MapShape(X,Y,W,HEIGHT*0.1,Root)  //def
{
}

Trap* Platform::addTrap()
{
	return new Trap(x+rand()%(int)(w-HEIGHT*0.1),y-HEIGHT*0.05,root);   //def
}

DeathBall* Platform::addDB()
{
	return new DeathBall(x+w*0.5+rand()%int(w*0.25), y-HEIGHT*0.16-root->getNinja()->r*2.1, HEIGHT*0.16, root);  //def
}

Archer* Platform::addArcher()
{
	return new Archer(x+rand()%(int)w,y,root);
}

void Platform::draw()
{
	Graphics::color(0,0,0);
	Graphics::rectangle(root->toX(x),root->toY(y),root->toL(w),root->toL(h));
}

void Platform::move()
{
	x-=root->speed;
	if(x<root->getNinja()->x && x+w>root->getNinja()->x)
	{
		//root->getNinja()->setBorder(y);
	}
}

DeathBall::DeathBall(float X,float Y,float R,GameCore* Root):MapShape(X,Y,R*2,R*2,Root)
{
	r=R;
}

void DeathBall::draw()
{
	Graphics::color(0,0,1);
	Graphics::circle(root->toX(x),root->toY(y),root->toL(r));
	Graphics::rectangle(root->toX(x-HEIGHT*0.02),0,root->toL(HEIGHT*0.04),root->toY(y-r));  //def
}

void DeathBall::move()
{
	x-=root->speed;
	float _x=root->getNinja()->x;
	float _y=root->getNinja()->y;
	float _h=root->getNinja()->h;
	if( (_x-x)*(_x-x)+(_y-y)*(_y-y)<r*r || (_x-x)*(_x-x)+(_y-y-_h)*(_y-y-_h)<r*r)
	{
		root->getNinja()->setState(5);
	}
}


Archer::Archer(float X,float Y,GameCore* Root):MapShape(X,Y,0,0,Root)
{
	angle=180;
	y0=-1000;//def
}

void Archer::draw()
{
	Graphics::color(0,1,0);
	Graphics::circle(root->toX(x),root->toY(y-HEIGHT*0.05*2),root->toL(HEIGHT*0.05));
}

void Archer::move()
{
	x-=root->speed;
	for(std::list<Point*>::iterator it=targets.begin();it!=targets.end();it++)
	{
		(*it)->x-=root->speed;
	}
}

void Archer::addTarget(Point* P)
{
	targets.push_back(P);
}

Arrow* Archer::shoot()
{
	Point* p=targets.front();
	targets.pop_front();
	float x1=x;
	float y1=y;
	float x2=p->x;
	float y2=p->y;
	
	float d=(y2-y0)*(y1-y0);
	float dx=x1-x2;

	//if(d>=0 && dx)  nnada?
	//{
		float a=(y1+y2-2*y0+2*sqrt(d))/(dx*dx);
		float b=(y1-y2)/dx-a*(x1+x2);
		float c=(x1*y2-x2*y1)/dx+a*x1*x2;
		float GRAV=1;
		float vx=dx/(GRAV*(sqrt(y1-y0)+sqrt(y2-y0)));
	//}

	return new Arrow(x,y/*-HEIGHT*0.1*/,a,b,c,vx,p,root);


}

Arrow::Arrow(float X,float Y,float A,float B,float C,float Vx,Point* Target,GameCore* Root):MapShape(X,Y,0,0,Root)
{
	a=A;
	b=B;
	c=C;
	vx=Vx;
	px=X;
	target=Target;
	hit=false;
	rot=0;
}

void Arrow::move()
{
	x-=root->speed;
	target->x-=root->speed;
	if(!hit)
	{
		px-=vx;
		y=a*px*px+b*px+c;
		x-=vx;
		if(x<=target->x)
		{
			std::cout<<x<<" "<<target->x<<"\n";
			x=target->x;
			y=target->y;
			hit=true;
		}
	}
}

void Arrow::draw()
{
	Graphics::color(0,0,0);
	Graphics::circle(root->toX(x),root->toY(y),root->toL(HEIGHT*0.01));
}











