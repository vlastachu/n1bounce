#include "ModuleManager.h"
//#include "Module.h"

//using namespace std;
ModuleManager::ModuleManager()
{
	isDump=false;
}

void ModuleManager::Register(string name,Module* module)
{
	allModules.insert(std::pair<string,Module*>(name,module));
}

void ModuleManager::Start(string name)
{
	map<string,Module*>::iterator it=allModules.find(name);
	if(it!=allModules.end())
	{
		activeModules.insert(std::pair<string,Module*>(name,it->second));
		it->second->setManager(this);//NULL->Init()
		it->second->Init();//NULL->Init()
	}
}

void ModuleManager::Start(string name,map<string, void*> params)
{
	map<string,Module*>::iterator it=allModules.find(name);
	if(it!=allModules.end())
	{
		activeModules.insert(std::pair<string,Module*>(name,it->second));
		it->second->setManager(this);//NULL->Init()
		it->second->send(params);
		it->second->Init();//NULL->Init()
		
	}
}

void ModuleManager::Stop(string name)
{
	dump.push_back(name);
	isDump=true;
}

void ModuleManager::Run()
{
	//cout<<2;
	for(map<string,Module*>::iterator it=activeModules.begin();it!=activeModules.end();it++)
	{
		it->second->Run();//NULL->Run()
	}
	//cout<<6;
	if(isDump)
	{
		for(vector<string>::iterator it=dump.begin();it!=dump.end();it++)
		{
			activeModules.find(*it)->second->Clear();//NULL->Clear()
			activeModules.erase(*it);
		}
		dump.clear();
		isDump=false;
	}
}

