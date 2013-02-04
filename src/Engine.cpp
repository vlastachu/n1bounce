#include "Engine.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"
#include <iostream>

Engine::Engine()
{
	map.init();
	ball.init();
}

Engine& Engine::Instance()
{
        static Engine theSingleInstance;
        return theSingleInstance;
}

void Engine::gameOver(char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		map.clear();
		map.init();
		ball.init();
}

void Engine::play()
{
	map.move();
	map.draw();
	ball.move();
	ball.draw();

	ball.setborder(HEIGHT+1); 
	for(auto platform : map.getPlatforms()){
		if(platform->getx()-7 < ball.getx() && platform->getx() + platform->getw() > ball.getx()) //laa'ag
		{
			ball.setborder(platform->gety());
		}
	}
	for(auto trap : map.getTraps()){
		if(trap->getx() < ball.getx() && trap->getx() + trap->getw() > ball.getx()
			&& trap->gety() - trap->geth() < ball.gety() && trap->gety() > ball.gety())
			{
				gameOver("trap");
			}
	}
	
	if(ball.gety() >= HEIGHT)
	{
		gameOver("deadline");
	}
}