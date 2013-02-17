#pragma once
#include "Map.h"
//#include "Ball.h"
#include "Module.h"
#include "Ninja.h"

/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*/
class Map;
class Ninja;
class GameCore:public Module
{
	Ninja* man;//destructor
	Map* g_map;
	//Ball ball;
	int score;
	bool _gameOver;
	
	void glutPrint(float x, float y, void* font, string text);
public:
	float toX(float X);
	float toY(float Y);
	float toL(float L);
	float speed;
	float scale;
	void gameOver(const char* also);
	Ninja* getNinja(){return man;}
	GameCore();
	virtual void keyPressed(unsigned char key);
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};