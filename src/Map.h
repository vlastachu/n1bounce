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

class GameCore;
class Map
{
	GameCore* parent;
	struct Element
	{
		float x,y,w,h;
		int id;
		Element(float X,float Y,float W,float H,int Id)
		{
			x=X;y=Y;w=W;h=H;id=Id;
		}

	};

	int randW, randY, directionY, deltaY;
	std::list<Element> elements;
	//float speed;
	int dist;
public:
	Map(GameCore* Parent);
	void draw();
	void init();
	void move();
};
