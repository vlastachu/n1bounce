#pragma once
#include "GraphicShape.h"

class FixedMapShape: public GraphicShape
{
protected:
		float w,h;

public:
	virtual void move(float dx);
	virtual void keyPressed (unsigned char key)=0;
	float getw();
	float geth();
	~FixedMapShape(){};
};
