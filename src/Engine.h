#pragma once
#include "Map.h"
#include "Ball.h"
/*
 Engine provides all the application
 This class agregating the Map and the Ball objects
 TODO: singleton
*/

class Engine
{
private:
Map map;
Ball ball;
Engine();
Engine(const Engine& root);
Engine& operator=(const Engine&);
void gameOver(char* also);
public:
Ball* getBall(){
	return &ball;
}
static Engine& Instance();
void play();
};
