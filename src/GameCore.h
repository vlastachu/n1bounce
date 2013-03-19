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
<<<<<<< HEAD
	Text *text;
	Background *back1, *back2, *back3;
=======
	void glutPrint(float x, float y, void* font, string text);

>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
public:
	float toX(float X);
	float toY(float Y);
	float toL(float L);
	float speed;
	float scale;
	void gameOver(const char* also);
	Ninja* getNinja(){return man;}
	GameCore();
<<<<<<< HEAD
	virtual void send(map<string, void*> params);
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
	virtual void keyPressed(int Key);
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();
	virtual void Clear();
};