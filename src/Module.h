#pragma once
#include "ModuleManager.h"
class ModuleManager;
class Module
{
protected:
	ModuleManager* mgr;
public:
	void setManager(ModuleManager* Mgr)
	{
		mgr=Mgr;
	}
	
	virtual void init(Module* Sender){}
	virtual void run(){}
	virtual void clear(){}
	virtual void keyPressed(int Key){}
	virtual void keyReleased(int Key){}
};