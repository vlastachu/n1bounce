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

struct Point
{
	float x,y;
	Point(float X,float Y)
	{
		x=X;y=Y;
	}
};

class Arrow:public MapShape
{
	Point* target;
	float a,b,c;
	float rot;
	float vx;//xspeed
	float px;//parabola x
	//float spx;//start parabola x
	bool hit;
public:
	Arrow(float X,float Y,float A,float B,float C,float Vx,Point* Target,GameCore* Root);
	virtual void move();
	virtual void draw();
};

class Archer:public MapShape
{
	std::list<Point*> targets;
	float angle;
	float y0;
public:
	Archer(float X,float Y,GameCore* Root);
	virtual void draw();
	virtual void move();
	Arrow* shoot();
	void addTarget(Point* P);
};

class Trap:public MapShape   //TODO: static const width...hmmm, maybe not
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
	Archer* addArcher();
	virtual void draw();
	virtual void move();
};






class Map
{
	GameCore* root;
	Archer* archBoss;//kostil
	
	//int randW, randY, directionY, deltaY;
	std::list<MapShape*> elements;
	int dist;
	Platform* lastPlat;
	Platform* addPlatform();
public:
	Map(GameCore* Parent);
	void draw();
	void init();
	void move();
};
