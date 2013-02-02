#pragma once
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Trap: public FixedMapShape
{
public:
	void draw(); //overrided
	Trap(int Y, int X);
	~Trap(){}
};