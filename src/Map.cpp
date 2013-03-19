#include "Map.h"

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

	Platform* p=new Platform(-100,500,WIDTH,root);       //    UNSAFE NULL->x
	elements.push_back(p);
	lastPlat=p;
}

void Map::move()
{

	if(root->toX(lastPlat->x + lastPlat->w - PLATFORM_DISTANCE) <= WIDTH)  
	{
		float deltaY=rand()%150;
		float directionY=rand()%2;
		if(directionY==0) directionY=-1;
		if(lastPlat->y+deltaY>500)
		{
			directionY=-1;
		}
		else if(lastPlat->y-deltaY<40)
		{
			directionY=1;
		}
		
		Platform* p=new Platform(lastPlat->x+lastPlat->w+200,lastPlat->y+directionY*deltaY,200+rand()%300,root);
		lastPlat=p;
		elements.push_back(p);
		if(!(rand()%4))
		{
			elements.push_back(p->addTrap());
		}
		else if(p->w>350)
		{
			elements.push_back(p->addDB());
		}
	}

	if(!elements.empty())
	{
		if((elements.front()->x + elements.front()->w) < - WIDTH)//TODO: do it nicer
		{
			delete *elements.begin();
			elements.erase(elements.begin());
		}
	}


	root->getNinja()->setBorder(2*HEIGHT);
	for(std::list<MapShape*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->x-=root->speed;
		(*it)->move();
	}
	
}




//____MapShape____________________________________________________________________________________________________




MapShape::MapShape(float X,float Y,float W,float H,int Id,GameCore* Root)
{
	x=X;y=Y;w=W;h=H;id=Id,root=Root;
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

Trap* Platform::addTrap()
{
	return new Trap(x+rand()%(int)(w-30),y-15,root);
}

DeathBall* Platform::addDB()
{
	return new DeathBall(x+w/4+rand()%int(w/2), y-50-root->getNinja()->r*2, 50, root);
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

void DeathBall::draw()
{
	Graphics::color(0,0,1);
	Graphics::circle(root->toX(x),root->toY(y),root->toL(r));
	Graphics::rectangle(root->toX(x-5),0,root->toL(10),root->toY(y-r));
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