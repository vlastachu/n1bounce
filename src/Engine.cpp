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

void Engine::play()
{
	map.move();
	map.draw();
	ball.move();
	ball.draw();

	if(ball.gety() >= DEAD_LINE)
	{
		std::cout << "GAME OVER! Try again.\n";
		exit(0);
	}
}