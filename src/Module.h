#pragma once
#include "ModuleManager.h"
//class ModuleManager;
class Module
{
	friend class ModuleManager;
	bool Freeze;
	void setManager(ModuleManager* Mgr)
	{
		Freeze=false;
		mgr=Mgr;
	}
protected:
	ModuleManager* mgr;
public:
	virtual void Init(){}//TODO: think about friends
	virtual void Run(){}
	virtual void Clear(){}
	virtual void keyPressed(int Key){}
	virtual void keyReleased(int Key){}
};

