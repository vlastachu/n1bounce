#include <iostream>
#include <GL\glut.h>
#include "GameCore.h"
#include "Map.h"
#include "defs.h"


//#include "EventManager.h"
///coment
GameCore::GameCore()
{
	g_map=new Map(this);
	man=new Ninja(this);
	EventManager::Instance().Register(this);
}

void GameCore::keyPressed(unsigned char key)
{
	man->jump();
}

void GameCore::Init()
{
	//e_mgr.Add(&ball);
	g_map->init();
	//ball.init();
	man->init();
}

void GameCore::Clear()
{
}

void GameCore::gameOver(char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		score = 0;
		g_map->init();
		man->init();
}

void GameCore::glutPrint(float x, float y, void* font, string text) 
{ 
    glRasterPos2f(x,y); 
    for (int i=0; i<text.size(); i++)
    {
        glutBitmapCharacter(font, text[i]);
    }
}
void GameCore::Run()
{
	man->move();
	man->draw();
	g_map->move();
	g_map->draw();
	/*ball.move();
	ball.draw();*/
	
	
	//score:
	score++;
	string sScore = "score: ";
	char chScore[10]; itoa(score,chScore,10);
	sScore+=chScore;
	glutPrint(800,20,GLUT_BITMAP_TIMES_ROMAN_24,sScore);
	
	
	if(man->y >= HEIGHT)
	{
		gameOver("deadline");
	}
}