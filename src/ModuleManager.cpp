#include "ModuleManager.h"
#include <iostream>

ModuleManager::ModuleManager()
{
	activeModule=NULL;
}

void ModuleManager::registrate(string Name,Module* module)
{
	modules.insert(std::pair<string,Module*>(Name,module));
	modules.find(Name)->second->setManager(this);
}


void ModuleManager::run()
{
	if(activeModule)
		activeModule->run();
}

void ModuleManager::setModule(string Name)
{
	Module* sender=activeModule;
	if(activeModule)
		activeModule->clear();
	map<string,Module*>::iterator it = modules.find(Name);
	if(it!=modules.end())
	{
		activeModule=it->second;
		//std::cout<<activeModule;
		if(activeModule)
		{
			std::cout<<Name;
			activeModule->init(sender);
		}
	}
}

/*Module* ModuleManager::getModule(string Name)
{
	map<string,Module*>::iterator it = modules.find(Name);
	if(it!=modules.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}*/

Module* ModuleManager::getActiveModule()
{
	return activeModule;
}