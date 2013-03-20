#pragma once
#include "Module.h"
#include "Font.h"

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
		mgr->setModule("game",false);
	}
	virtual void keyReleased(int Key)
	{		
	}
};