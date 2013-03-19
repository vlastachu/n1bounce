#pragma once
#include <map>
#include <vector>
#include <string>
//using namespace std;
using std::string;
using std::map;
using std::vector;
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
	
	virtual void Init(){}
	virtual void Run(){}
	virtual void Clear(){}
	virtual void keyPressed(int Key){}
	virtual void keyReleased(int Key){}
	virtual void mouse(int button, int state, int x, int y){};
	virtual void mousePasive(int x, int y){}
	virtual void send(map<string, void*> params){}
};