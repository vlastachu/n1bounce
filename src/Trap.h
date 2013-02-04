#pragma once
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Trap: public FixedMapShape
{
public:
	int u;
	void draw(); //overrided
	Trap(int Y, int X);
	~Trap(){}
};