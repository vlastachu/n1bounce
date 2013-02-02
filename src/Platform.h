#pragma once
#include "FixedMapShape.h"
#include "GraphicShape.h"
class Platform: public FixedMapShape
{
public:
	void draw(); //overrided
	Platform();
	~Platform(){}
};