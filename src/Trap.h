#pragma once
#include "defs.h"
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Trap: public FixedMapShape
{
public:
	virtual void keyPressed (unsigned char key){};
	int u;
	void draw(); //overrided
	Trap(int Y, int X);
	ClassType getType();
	~Trap(){}
};