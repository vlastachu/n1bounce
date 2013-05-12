#include <GL\GL.H>
#include "GameCore.h"
#include <time.h>
#include "Events.h"


GameCore::GameCore()
{
	g_map=new Map(this);
	man=new Ninja(this);
	gameState=new GameState(GAME);
}

void GameCore::init(Module* Sender)
{
	srand(time(NULL));

	xScaleAxis=HEIGHT*0.4; //def
	yScaleAxis=HEIGHT;

	scale=1;
	score = 0;
	speed = HEIGHT/40;  //def
	_gameOver=false;
	_pause=false;
	_key=false;
	g_map->init();
	man->init();

	*gameState=GAME;
}

void GameCore::clear()
{
}

void GameCore::gameOver(const char* also){
		//std::cout << "GAME OVER! Try again." << also << "\n";
		_gameOver=true;
}

void GameCore::run()
{
	
	/*glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(0,0);
		glVertex2f(WIDTH,0);
		glColor3f(0.1f,0.0f,0.1f);
		glVertex2f(WIDTH,HEIGHT);
		glVertex2f(0,HEIGHT);
	glEnd();*/
	Graphics::color(0,0,0);
	Graphics::rectangle(20,20,30,30);

	if(Events::instance().mouseEvent==Events::CLICK)
	{
		
		float x=Events::instance().x;
		float y=Events::instance().y;
		if(x>20 && x<50 && y>20 && y<50)
		{
			Events::instance().reset();
			if(*gameState==GAME)
				*gameState=PAUSE;
			else
				*gameState=GAME;
		}
	}

	if(Events::instance().kbdEvent==Events::RELEASE)
	{
		switch(Events::instance().key)
		{
		case KEY_UP:
			man->jump();
			break;
		case KEY_DOWN:
			man->slide();
			break;
		case KEY_RIGHT:
			speed++;
			break;
		case KEY_LEFT:
			_pause=true;
			break;
		}
	}


	if(*gameState==GAME)
	{
		man->move();
		g_map->move();
	}

	man->draw();
	g_map->draw();

	if(*gameState==GAME)
	{
		scale=1-(yScaleAxis-man->y)/(HEIGHT * 3);  //TODO: exp() function or smth like that

		score++;
	}

	string sScore = "Score: ";
	char chScore[10];
	_itoa_s(score,chScore,10);
	sScore+=chScore;
	

	//Graphics::outTextXY(WIDTH-300,10,20,20,sScore.c_str(),"dbg_font");
	Font::findByName("std")->draw(sScore.c_str(),WIDTH-300,10,20, 0, 0, 0);//TODO: find once and use pointer to draw
	if(_gameOver)
		mgr->setModule("g_over");
	if(_pause)
	{
		_pause=false;
		mgr->setModule("start");
	}
}

float GameCore::toX(float X)
{
	return xScaleAxis+(X-xScaleAxis)*scale;
}

float GameCore::toY(float Y)
{
	return yScaleAxis+(Y-yScaleAxis)*scale;
}

float GameCore::toL(float L)
{
	return L*scale;
}