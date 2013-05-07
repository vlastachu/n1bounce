#pragma once
#include "Module.h"
#include <iostream>

class StartMenu:public Module
{
public:
	StartMenu()
	{
		
	}
	void init(Module* Sender){}
	void run();
	void clear(){}
};