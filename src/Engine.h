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

public:
void reshape(int w, int h);
void motion(int X,int Y);
void mouse(int button, int state, int x, int y);
void display();
void TimerFunction(int value);
void keyPressed (unsigned char key, int x, int y);


	Engine(int argc, char * argv[]);
	void play();
};
