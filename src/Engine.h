#pragma once
#include "GameCore.h"
#include "ModuleManager.h"
/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*////

class Engine
{
private:
	ModuleManager mgr;
	GameCore game;
	Engine();
	//Engine(const Engine& root);
	//Engine& operator=(const Engine&);
	//void gameOver(char* also);
public:
	static Engine& Instance();
	void play();
	/*GameCore* getGame()
	{
		return &game;
	}*/
	};
