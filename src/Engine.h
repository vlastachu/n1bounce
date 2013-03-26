#pragma once
#include "GameCore.h"
#include "Pause.h"
#include "ModuleManager.h"

class Engine
{
private:
	GameCore* game;
	Pause* pause;
	Font* font;
	Engine();
	
public:
	ModuleManager* mgr;
	Font* getFont(){return font;}
	void keyPressed(int Key);
	void keyReleased(int Key);
	void mouse(int button, int state, int x, int y);
	void mousePasive(int x, int y);
	void play();
	static Engine& Instance();
	
	//void reshape(int Width, int Height);
};