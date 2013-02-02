#pragma once
#include "GraphicShape.h"
//Ball is a singleton class 

class Ball: public GraphicShape
{
	float r, dy, yborder;
	bool jmp;
	int impulse;
public:
	Ball(); //TODO: think about it

	void setborder(float Y);
	void init();
	void jump();
	void move();
	void draw(); //overrided
};