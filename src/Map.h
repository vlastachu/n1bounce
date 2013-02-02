#pragma once
#include <vector>
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
	int randW, randY;
	std::vector<FixedMapShape*> shapes;
	std::vector<Platform*> platforms;
	std::vector<Trap*> traps;
	float speed;
	int dist;
public:
	Map();
	void draw();
	void init();
	void move();
	void clear();
	std::vector<Platform*> getPlatforms();
	std::vector<Trap*> getTraps();

};
