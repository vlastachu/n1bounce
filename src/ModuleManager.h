#pragma once
#include "Module.h"
#include <map>
#include <vector>
#include <string>
//using namespace std;
using std::string;
using std::map;
using std::vector;
class Module;
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
	void Start(string name,map<string, void*> params);
	void Stop(string name);
};