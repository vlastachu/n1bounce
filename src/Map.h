#pragma once
#include <list>
#include "FixedMapShape.h"
#include "defs.h"
#include "Ball.h"
#include "Platform.h"
#include "Trap.h"
/*
Platforms before;
Contains FixedMapShape objects and provides control for their movement
*/

class Map
{
	int randW, randY, directionY, deltaY;
	std::list<FixedMapShape*> shapes;
	std::list<Platform*> platforms;
	std::list<Trap*> traps;
	float speed;
	int dist;
public:
	Map();
	void draw();
	void init();
	void move();
	void clear();
	std::list<Platform*> getPlatforms();
	std::list<Trap*> getTraps();

};
