#include "Map.h"
#include "Engine.h"

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
}

void Map::move()
{

	if(root->toX(lastPlat->x + lastPlat->w + HEIGHT/2) <= WIDTH)  //def
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
		if(!(rand()%4))
		{
			elements.push_back(p->addTrap());
		}
		else if(p->w>HEIGHT)   //def
		{
			elements.push_back(p->addDB());
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


	root->getNinja()->setBorder(2*HEIGHT);  //TODO: do it nicer
	for(std::list<MapShape*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->x-=root->speed;
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
	return new DeathBall(x+w*0.5+rand()%int(w*0.25), y-HEIGHT*0.16-root->getNinja()->r*2*1.1, HEIGHT*0.16, root);  //def
}

void Platform::draw()
{
	Graphics::color(0,0,0);
	Graphics::rectangle(root->toX(x),root->toY(y),root->toL(w),root->toL(h));
}

void Platform::move()
{
	if(x<root->getNinja()->x && x+w>root->getNinja()->x)
	{
		root->getNinja()->setBorder(y);
	}
}

DeathBall::DeathBall(float X,float Y,float R,GameCore* Root):MapShape(X,Y,R*2,R*2,Root)
{
	r=R;
}

void DeathBall::draw()
{
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(root->toX(x-HEIGHT*0.02),0,root->toL(HEIGHT*0.04),root->toY(y));  //def
	Graphics::draw(0,0,1,1,root->toX(x-r),root->toY(y-r),root->toL(2*r),root->toL(2*r),0,0,0,"db");
	
	//Graphics::circle(root->toX(x),root->toY(y),root->toL(r));
}

void DeathBall::move()
{
	float _x=root->getNinja()->x;
	float _y=root->getNinja()->y;
	float _h=root->getNinja()->h;
	if( (_x-x)*(_x-x)+(_y-y)*(_y-y)<r*r || (_x-x)*(_x-x)+(_y-y-_h)*(_y-y-_h)<r*r)
	{
		root->getNinja()->setState(5);
	}
}