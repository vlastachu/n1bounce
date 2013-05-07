#pragma once
#include "Map.h"
#include "Module.h"
#include "Ninja.h"
#include "Engine.h"

class Map;
class Ninja;
class GameCore:public Module
{
	Ninja* man;
	Map* g_map;
	enum GameState
	{
		GAME,PAUSE
	}*gameState;
	
	bool _gameOver;
	bool _pause;
	bool _key;
	
	float yScaleAxis;
public:
	int score;
	float xScaleAxis;//TODO: method
	float toX(float X);
	float toY(float Y);
	float toL(float L);
	float speed;
	float scale;
	void gameOver(const char* also);//TODO: ubrat' naxuy
	Ninja* getNinja(){return man;}
	Map* getMap(){return g_map;}
	GameCore();

	void init(Module* Sender);
	void run();
	void clear();
};