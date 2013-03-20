#pragma once
#include "Module.h"

class Font;
class Pause:public Module
{
public:
	Pause()
	{
	}
	virtual void Init(){}
	virtual void Run();
	virtual void Clear(){}
	virtual void keyPressed(int Key)
	{
		mgr->setModule("game");
	}
	virtual void keyReleased(int Key)
	{		
	}
};