#pragma once
#include "Graphics.h"
#include "GameCore.h"

class GameCore;
class Ninja
{
	float dragX0,dragY0;

	float dy,impulse;
	int jmp;
	
	float borderY;
	float prevY;

	GameCore* parent;
	float phase;
	
	int state;	
	struct Element 
	{
		float x,y,h,w,rot;
		//unsigned texture;
	};
	Element leg1,leg2,body,katana;
public:
	void setBorder(float Y)
	{
		borderY=Y;
	};
	void jump();
	void slide();
	//void mapCollise(float Y,float H, int Id);
	Ninja(GameCore* Parent);
	float x,y,r,h;
	//int getState(){return state;}
	void setState(int State){state=State;phase=0;};
	void init();
	void draw();
	void move();
};