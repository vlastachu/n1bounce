#pragma once
#include "GraphicShape.h"

class FixedMapShape: public GraphicShape
{
protected:
		float w,h;

public:
	virtual void move(float dx);
	float getw();
	float geth();
	~FixedMapShape(){};
};
