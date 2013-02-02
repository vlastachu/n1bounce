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

void Engine::gameOver(){
		std::cout << "GAME OVER! Try again.\n";
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

	ball.setborder(HEIGHT); 
	auto platforms = map.getPlatforms();
	for(int i=0; i < platforms.size(); i++)
	{
		if(platforms.at(i)->getx() < ball.getx() && platforms.at(i)->getx() + platforms.at(i)->getw() > ball.getx())
		{
			ball.setborder(platforms.at(i)->gety());
		}
	}
	auto traps = map.getTraps();
	for(int i=0; i < traps.size(); i++)
	{
		if(traps.at(i)->getx() < ball.getx() && traps.at(i)->getx() + traps.at(i)->getw() > ball.getx()
			&& traps.at(i)->gety() - traps.at(i)->geth() < ball.gety() && traps.at(i)->gety() > ball.gety())
		{
			gameOver();
		}
	}
	
	if(ball.gety() >= DEAD_LINE)
	{
		gameOver();
	}
}