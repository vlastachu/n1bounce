#pragma once
#include "GameCore.h"
#include <list>
//#include "FixedMapShape.h"
#include "defs.h"
//#include "Ball.h"
//#include "Platform.h"
//#include "Trap.h"

/*
Platforms before;
Contains FixedMapShape objects and provides control for their movement
*/

class MapShape
{
public:
	float x,y,w,h;
	int id;

	MapShape(float X,float Y,float W,float H,int Id)
	{
		x=X;y=Y;w=W;h=H;id=Id;
	}
	//virtual void draw()=0;
};

class Trap:public MapShape
{
public:
	Trap(float X,float Y):MapShape(X,Y,30,15,2){};
	//virtual void draw();
};

class Platform:public MapShape
{
public:
	Platform(float X,float Y,float W):MapShape(X,Y,W,30,1){};
	Trap* addTrap()
	{
		return new Trap(x+rand()%(int)(w-30),y-15);
	}
	//virtual void draw();
};


class GameCore;
class Map
{
	GameCore* parent;
	/*struct Element
	{
		float x,y,w,h;
		int id;
		Element(float X,float Y,float W,float H,int Id)
		{
			x=X;y=Y;w=W;h=H;id=Id;
		}

	};*/

	int randW, randY, directionY, deltaY;
	std::list<MapShape*> elements;
	//float speed;
	int dist;
	Platform* lastPlat;
public:
	Map(GameCore* Parent);
	void draw();
	void init();
	void move();
};
