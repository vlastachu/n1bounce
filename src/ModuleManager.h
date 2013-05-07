#pragma once
#include "Module.h"
#include <map>
#include <string>

#define string std::string
#define map std::map
class Module;
class ModuleManager
{
	map<string,Module*> modules;
	Module* activeModule;
public:
	ModuleManager();
	void setModule(string Name);
	void run();
	void registrate(string name,Module* module);
//	Module* getModule(string Name);
	Module* getActiveModule();
};