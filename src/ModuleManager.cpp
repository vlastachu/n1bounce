#include "ModuleManager.h"

ModuleManager::ModuleManager()
{
	activeModule=NULL;
}

void ModuleManager::Register(string Name,Module* module)
{
	modules.insert(std::pair<string,Module*>(Name,module));
	modules.find(Name)->second->setManager(this);
}


void ModuleManager::Run()
{
	if(activeModule)
		activeModule->Run();
}

void ModuleManager::setModule(string Name,bool Freeze)
{
	if(activeModule)
	{
		activeModule->Freeze=Freeze;
		if(!activeModule->Freeze)
			activeModule->Clear();
	}

	map<string,Module*>::iterator it = modules.find(Name);
	if(it!=modules.end())
	{
		activeModule=it->second;
		if(activeModule)
			if(activeModule->Freeze)
				activeModule->Freeze=false;
			else
				activeModule->Init();
	}
}

Module* ModuleManager::getModule(string Name)
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
}

Module* ModuleManager::getActiveModule()
{
	return activeModule;
}