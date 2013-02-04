#pragma once
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Platform: public FixedMapShape
{
public:
	void draw(); //overrided
	Platform();
	Platform(int Y, int width);
	Platform(int Y, int width, int X);
	~Platform(){}
};