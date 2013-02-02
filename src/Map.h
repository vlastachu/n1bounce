#pragma once
#include <vector>
#include "FixedMapShape.h"
#include "defs.h"
#include "Ball.h"
/*
Platforms before;
Contains FixedMapShape objects and provides control for their movement
*/

class Map
{
	std::vector<FixedMapShape*> shapes;
	float speed;
	int dist;
public:
	Map();
	void draw();
	void init();
	void move();
};
