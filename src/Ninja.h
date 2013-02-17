#pragma once

#include "EventManager.h"
#include "Graphics.h"
#include "GameCore.h"

//#include "Leg.h"
//#include <vector>
//using namespace std;
//#define vector std::vector


//class Leg;
//class Animation;
//class AnimManager;
class GameCore;
class Ninja
{
	float dy,impulse;
	int jmp;
	
	float borderY;
	float prevY;

	GameCore* parent;
	float phase;
	float speed;
	int state;	
	struct Element 
	{
		float x,y,h,w,rot;
		unsigned texture;
	};
	Element leg1,leg2,body,katana;
public:
	void setBorder(float Y)
	{
		borderY=Y;
	};
	bool air;
	void jump();
	//void mapCollise(float Y,float H, int Id);
	Ninja(GameCore* Parent);
	float x,y,r;
	//int getState(){return state;}
	void setState(int State){state=State;phase=0;};
	void init();
	void draw();
	void move();
};