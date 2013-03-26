#pragma once
#include "Map.h"
#include "Module.h"
#include "Ninja.h"

class Map;
class Ninja;
class GameCore:public Module
{
	Ninja* man;
	Map* g_map;
	
	int score;
	bool _gameOver;
	bool _pause;
	bool _key;
	
	float yScaleAxis;
public:
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
	virtual void keyPressed(int Key);
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};