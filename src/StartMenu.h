#pragma once
#include "Module.h"
#include <iostream>

class StartMenu:public Module
{
public:
	StartMenu()
	{
		std::cout<<"4";
	}
	void init(Module* Sender){std::cout<<"4";}
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