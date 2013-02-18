#pragma once
#include "Module.h"
class EventManager
{
	Module* m;
public:
	void Register(Module* M)
	{
		m=M;
	}
	void keyPressed(int Key)
	{  
		m->keyPressed(Key);
	}
	void keyReleased(int Key)
	{
		m->keyReleased(Key);
	}
	static EventManager& Instance()
    {
            static EventManager theSingleInstance;
            return theSingleInstance;
    }
};
