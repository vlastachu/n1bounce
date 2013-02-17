#pragma once
#include "Module.h"
//#include <vector>

//class Ninja;
class EventManager
{
	Module* m;
public:
	void Register(Module* M)
		{
	m=M;
};
	void keyPressed (int key)
		{  
	//std::cout<<ninja;
	if(!m)
		exit (9);
	m->keyPressed(key);
}
	static EventManager& Instance()
    {
            static EventManager theSingleInstance;
            return theSingleInstance;
    }
};
