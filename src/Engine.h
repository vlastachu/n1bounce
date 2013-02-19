#pragma once
#include "GameCore.h"
#include "ModuleManager.h"
#include "Final.h"
#include "Module.h"
/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*////

class Engine
{
private:
	GameCore game;
	Final fin;
	Engine();
	//Engine(const Engine& root);
	//Engine& operator=(const Engine&);
	//void gameOver(char* also);
public:
	ModuleManager mgr;
	static Engine& Instance();
	void play();
	/*GameCore* getGame()
	{
		return &game;
	}*/
	};
