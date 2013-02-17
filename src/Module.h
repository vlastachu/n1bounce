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
	
	virtual void Init(){};
	virtual void Run(){};
	virtual void Clear(){};
	virtual void keyPressed(int key){}
};