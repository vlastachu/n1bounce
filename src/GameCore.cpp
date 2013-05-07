#include "GameCore.h"
GameCore::GameCore()
{
	g_map=new Map(this);
	man=new Ninja(this);
}

void GameCore::keyPressed(int Key)
{
	if(!_key)
	{
		switch(Key)
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
		_key=true;
	}
}

void GameCore::keyReleased(int Key)
{
	_key=false;
}

void GameCore::Init()
{
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
}

void GameCore::Clear()
{
}

void GameCore::gameOver(const char* also){
		//std::cout << "GAME OVER! Try again." << also << "\n";
		_gameOver=true;
}

void GameCore::Run()
{
	man->move();
	man->draw();
	g_map->move();
	g_map->draw();
	
	scale=1-(yScaleAxis-man->y)/(HEIGHT * 3);  //TODO: exp() function or smth like that

	score++;
	string sScore = "Score: ";
	char chScore[10]; itoa(score,chScore,10);
	sScore+=chScore;
	//Text::draw(sScore.c_str(),0.85,0.05,"gameinfo");
	Graphics::outTextXY(HEIGHT*1.5,HEIGHT*0.05,129,129,sScore.c_str(),"../fonts/Ubuntu-m.ttf");
	if(_gameOver)
		Init();
	if(_pause)
	{
		_pause=false;
		mgr->setModule("pause");
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