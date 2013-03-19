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
	void mouse(int button, int state, int x, int y)
	{
		m->mouse(button, state, x, y);
	}
	void mousePasive(int x, int y)
	{
		m->mousePasive(x, y);
	}
	static EventManager& Instance()
    {
            static EventManager theSingleInstance;
            return theSingleInstance;
    }
};
