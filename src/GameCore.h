#pragma once
#include "Module.h"
#include "Text.h"
#include "Map.h"
#include "Ninja.h"
#include "Background.h"
/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*/
class Map;
class Ninja;
class GameCore:public Module
{
	Ninja* man;
	Map* g_map;
	int score;
	bool _gameOver;
	bool _key;
	Text *text;
	Background *back1, *back2, *back3;
public:
	float toX(float X);
	float toY(float Y);
	float toL(float L);
	float speed;
	float scale;
	void gameOver(const char* also);
	Ninja* getNinja(){return man;}
	GameCore();
	virtual void send(map<string, void*> params);
	virtual void keyPressed(int Key);
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};