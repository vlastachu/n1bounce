#pragma once
#include "GameCore.h"
#include <list>
#include "defs.h"
#include "Graphics.h"

//TODO: #define all defs

class GameCore;
class MapShape
{
protected:
	GameCore* root;
public:
	float x,y,w,h;
	
	MapShape(float X,float Y,float W,float H,GameCore* Root);
	virtual void draw()=0;
	virtual void move()=0;
};

class Trap:public MapShape   //TODO: static const width...
{
public:
	Trap(float X,float Y,GameCore* Root);
	virtual void draw();
	virtual void move();
};

class DeathBall:public MapShape
{
	float r;
public:
	DeathBall(float X,float Y,float R,GameCore* Root);
	virtual void draw();
	virtual void move();
};

class Platform:public MapShape
{
public:
	Platform(float X,float Y,float W,GameCore* Root);
	Trap* addTrap();
	DeathBall* addDB();
	virtual void draw();
	virtual void move();
};

//class BcgrTile:public 



class Map
{
	GameCore* root;
	
	//int randW, randY, directionY, deltaY;
	std::list<MapShape*> elements;
	//int dist;
	Platform* lastPlat;
public:
	Map(GameCore* Parent);
	void draw();
	void init();
	void move();
};
