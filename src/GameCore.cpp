#include <iostream>
#include <GL\glut.h>
#include "GameCore.h"

GameCore::GameCore()
{
	g_map=new Map(this);
	man=new Ninja(this);
	EventManager::Instance().Register(this);
}

void GameCore::keyPressed(int Key)
{
	if(!_key)
	{
		switch(Key)
		{
		case GLUT_KEY_UP:
			man->jump();
			break;
		case GLUT_KEY_DOWN:
			man->slide();
			break;
		case GLUT_KEY_RIGHT:
			speed++;
			break;
		}
		_key=true;
	}
}

void GameCore::keyReleased(int Key)
{
	_key=false;
}

void GameCore::Init()
{
	scale=1;
	score = 0;
	speed = 10;
	_gameOver=false;
	_key=false;
	g_map->init();
	man->init();
}

void GameCore::Clear()
{
}

void GameCore::gameOver(const char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		_gameOver=true;
}

void GameCore::glutPrint(float x, float y, void* font, string text) 
{
	glColor3f(0.0,0.7,0.5);
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
	
	scale=1-(YSCALE_AXIS-man->y)/(HEIGHT*2);
	//score:
	score++;
	string sScore = "score: ";
	char chScore[10]; itoa(score,chScore,10);
	sScore+=chScore;
	glutPrint(800,20,GLUT_BITMAP_TIMES_ROMAN_24,sScore);
	
	/*glEnable(GL_BLEND);
	glColor4f(0.0,1.0,0.0,0.2);
	glBegin(GL_LINES);
		glVertex2f(XSCALE_AXIS , 0);
		glVertex2f(XSCALE_AXIS , HEIGHT);
		glVertex2f(0 , YSCALE_AXIS);
		glVertex2f(WIDTH , YSCALE_AXIS);
	glEnd();
	glDisable(GL_BLEND);*/

	if(_gameOver)
		Init();
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