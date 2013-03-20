#pragma once
#include "GameCore.h"
#include <list>
#include "defs.h"
#include "Graphics.h"

/*
Platforms before;
Contains FixedMapShape objects and provides control for their movement
*/
class GameCore;
class MapShape
{
protected:
	GameCore* root;
public:
	float x,y,w,h;
	int id;
	
	MapShape(float X,float Y,float W,float H,int Id,GameCore* Root);
	virtual void draw()=0;
	virtual void move()=0;
};

class Trap:public MapShape
{
public:
	Trap(float X,float Y,GameCore* Root):MapShape(X,Y,30,15,2,Root){}
	virtual void draw();
	virtual void move();
};

class DeathBall:public MapShape
{
	float r;
public:
	DeathBall(float X,float Y,float R,GameCore* Root):MapShape(X,Y,R*2,R*2,3,Root)
	{
		r=R;
	}
	virtual void draw();
	virtual void move();
};

class Platform:public MapShape
{
public:
	Platform(float X,float Y,float W,GameCore* Root):MapShape(X,Y,W,30,1,Root){}
	Trap* addTrap();
	DeathBall* addDB();
	virtual void draw();
	virtual void move();
};




//class GameCore;
class Map
{
	GameCore* root;
	
	int randW, randY, directionY, deltaY;
	std::list<MapShape*> elements;
	int dist;
	Platform* lastPlat;
public:
	Map(GameCore* Parent);
	void draw();
	void init();
	void move();
};
