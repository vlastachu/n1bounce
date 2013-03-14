#pragma once
#include "GameCore.h"
#include "Pause.h"
#include "ModuleManager.h"

class Engine
{
private:
	ModuleManager* mgr;
	GameCore* game;
	Pause* pause;
	Font* font;
	Engine();
	
public:
	Font* getFont(){return font;}
	void keyPressed(int Key);
	void keyReleased(int Key);
	void play();
	static Engine& Instance();
	
	//void reshape(int Width, int Height);
};
