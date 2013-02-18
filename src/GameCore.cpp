#include "GameCore.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"
#include <iostream>
//#include "EventManager.h"
///coment
GameCore::GameCore()
{
}


void GameCore::Init()
{
	//e_mgr.Add(&ball);
	g_map.init();
	ball.init();
}

void GameCore::Clear()
{
	g_map.clear();
}

void GameCore::gameOver(char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		score = 0;
		g_map.clear();
		g_map.init();
		ball.init();
}

void GameCore::glutPrint(float x, float y, void* font, string text) 
{ 
    glColor4f(0,0,0,0);
    glRasterPos2f(x,y); 
    for (int i=0; i<text.size(); i++)
    {
        glutBitmapCharacter(font, text[i]);
    }
}
void GameCore::Run()
{
	g_map.move();
	g_map.draw();
	ball.move();
	ball.draw();
	
	//score:
	score++;
	string sScore = "score: ";
	char chScore[10]; itoa(score,chScore,10);
	sScore+=chScore;
	glutPrint(800,20,GLUT_BITMAP_TIMES_ROMAN_24,sScore);
	
	
	ball.setborder(-200); 
	std::list<FixedMapShape*> Plat = g_map.getPlatforms();
	for(std::list<FixedMapShape*>::iterator it = Plat.begin(); it != Plat.end(); it++){
		FixedMapShape* platform = *it;
		if(platform->getx()-7 < ball.getx() && platform->getx() + platform->getw() > ball.getx()) //laa'ag
		{
			ball.setborder(platform->gety());
		}
	}

	std::list<FixedMapShape*> Tr = g_map.getTraps();
	for(std::list<FixedMapShape*>::iterator it = Tr.begin(); it != Tr.end(); it++){
		FixedMapShape* trap = *it;
		if(trap->getx() < ball.getx() && trap->getx() + trap->getw() > ball.getx()
			&& trap->gety() - trap->geth() < ball.gety() && trap->gety() > ball.gety())
			{
				std::cout<<Tr.size()<<"\n";
				std::cout<<g_map.getShapes().size();
				gameOver("trap");
				
			}
	}
	
	if(ball.gety() >= HEIGHT)
	{
		gameOver("deadline");
	}
}