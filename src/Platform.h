#pragma once
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Platform: public FixedMapShape
{
public:
	virtual void keyPressed (unsigned char key){};
	void draw(); //overrided
	Platform();
	Platform(int Y, int width);
	Platform(int Y, int width, int X);
	~Platform(){}
};