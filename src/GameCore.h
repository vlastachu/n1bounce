#pragma once
#include "Map.h"
#include "Ball.h"
#include "Module.h"
/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*/

class GameCore:public Module
{
	Map g_map;
	Ball ball;
	void gameOver(char* also);
public:
	GameCore();
	Ball* getBall(){
		return &ball;
	}
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};