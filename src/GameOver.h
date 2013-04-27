#pragma once
#include "Module.h"

class GameOver:public Module
{
	int score;
public:
	GameOver()
	{
	}
	void init(Module* Sender);
	void run();
	void clear(){}
	void keyPressed(int Key)
	{
		mgr->setModule("game");
	}
	void keyReleased(int Key)
	{		
	}
};