#pragma once
#include "GameCore.h"
#include "GameOver.h"
#include "StartMenu.h"
#include "ModuleManager.h"


class Engine
{
private:
	ModuleManager* mgr;
	GameCore* game;
	StartMenu* start;
	GameOver* g_over;
	//Pause* pause;
	//Font* font;
	Engine();

	float w_height;
	float w_width;
	
public:
	float getWidth(){return w_width;};
	float getHeight(){return w_height;};

	//Font* getFont(){return font;}
	void play();
	static Engine& Instance();
	
	void reshape(float Width, float Height);
};