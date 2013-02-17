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
	if(key=='w')
		man->jump();
	if(key=='s')
		man->slide();
	if(key=='1')
		scale-=0.1;
	if(key=='2')
		speed++;
}

void GameCore::Init()
{
	scale=1;
	score = 0;
	speed = 10;
	g_map->init();
	man->init();
}

void GameCore::Clear()
{
}

void GameCore::gameOver(const char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		Init();
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
	
	scale=1-abs(YSCALE_AXIS-man->y)/(HEIGHT*4);
	//score:
	score++;
	string sScore = "score: ";
	char chScore[10]; itoa(score,chScore,10);
	sScore+=chScore;
	glutPrint(800,20,GLUT_BITMAP_TIMES_ROMAN_24,sScore);
	
	glEnable(GL_BLEND);
	glColor4f(0.0,1.0,0.0,0.2);
	glBegin(GL_LINES);
		glVertex2f(XSCALE_AXIS , 0);
		glVertex2f(XSCALE_AXIS , HEIGHT);
		glVertex2f(0 , YSCALE_AXIS);
		glVertex2f(WIDTH , YSCALE_AXIS);
	glEnd();
	glDisable(GL_BLEND);
	
}

float GameCore::toX(float X)
{
	return XSCALE_AXIS+(X-XSCALE_AXIS)*scale;
}

float GameCore::toY(float Y)
{
	return YSCALE_AXIS+(Y-YSCALE_AXIS)*scale;
}

float GameCore::toL(float L)
{
	return L*scale;
}