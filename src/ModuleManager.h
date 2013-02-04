#pragma once
#include "Module.h"
#include <map>
#include <vector>
#include <string>
//using namespace std;
#define string std::string
#define map std::map
#define vector std::vector
class ModuleManager
{
	map<string,Module*> allModules;
	map<string,Module*> activeModules;
	vector<string> dump;
	bool isDump;
public:
	ModuleManager();
	void Run();
	void Register(string name,Module* module);
	void Start(string name);
	void Stop(string name);
};