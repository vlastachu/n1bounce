#pragma once
#include "Map.h"
#include "Module.h"
#include "Ninja.h"
#include "Font.h"

class Map;
class Ninja;
class Font;
class GameCore:public Module
{
	Ninja* man;
	Map* g_map;
	int score;
	bool _gameOver;
	bool _key;
	bool _pause;
	void glutPrint(float x, float y, void* font, string text);
	
	float yScaleAxis;
public:
	float xScaleAxis;
	float toX(float X);
	float toY(float Y);
	float toL(float L);
	float speed;
	float scale;
	void gameOver(const char* also);
	Ninja* getNinja(){return man;}
	Map* getMap(){return g_map;}
	GameCore();
	virtual void keyPressed(int Key);
	virtual void keyReleased(int Key);                 //TODO: niceeeer!!! and no _key here!!!
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};

