#include <iostream>
#include <GL\glut.h>
#include "GameCore.h"
<<<<<<< HEAD
#include "Text.h"
#include "Engine.h"
=======

>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
GameCore::GameCore()
{
	g_map=new Map(this);
	man=new Ninja(this);
<<<<<<< HEAD
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

=======
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

>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
void GameCore::keyReleased(int Key)
{
	_key=false;
}

void GameCore::Init()
{
<<<<<<< HEAD
	back1 = (new Background())->setTexture("../data/sun.png")->setX(0.0);
	back2 = (new Background())->setTexture("../data/mountains.png")->setX(0.0001)->setY(80);
	back3 = (new Background())->setTexture("../data/groundc.png")->setX(0.0006)->setY(379);


	EventManager::Instance().Register(this);
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
	scale=1;
	score = 0;
	speed = 10;
	_gameOver=false;
	_key=false;
	g_map->init();
	man->init();
<<<<<<< HEAD
	text = (new Text())
		->setFont("../fonts/Ubuntu-m.ttf",33)
		->setShadow(true, 2, 2, 0.0, 0.38, 0.78,1.0)
		->setX(700)
		->setY(20)
		->setColor(1.0, 0.615, 0.29,1.0);
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
}

void GameCore::Clear()
{
<<<<<<< HEAD

=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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
<<<<<<< HEAD
	back1->draw();
	back2->draw();
	back3->draw();
=======
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
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
<<<<<<< HEAD
	text->setText(sScore)->draw();
=======
	glutPrint(800,20,GLUT_BITMAP_TIMES_ROMAN_24,sScore);
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
	
	/*glEnable(GL_BLEND);
	glColor4f(0.0,1.0,0.0,0.2);
	glBegin(GL_LINES);
		glVertex2f(XSCALE_AXIS , 0);
		glVertex2f(XSCALE_AXIS , HEIGHT);
		glVertex2f(0 , YSCALE_AXIS);
		glVertex2f(WIDTH , YSCALE_AXIS);
	glEnd();
	glDisable(GL_BLEND);*/

<<<<<<< HEAD
	if(_gameOver){
		map<string,void*> n;
		n.insert(std::pair<string,void*>("score",&score));
		Engine::Instance().mgr.Stop("game");
		Engine::Instance().mgr.Start("final",n);
	}
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

void GameCore::send(map<string, void*> params){

=======
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
>>>>>>> 6f577f6091c4cb8075629bed6f984bbb2234edac
}