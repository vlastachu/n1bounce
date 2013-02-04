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

	ball.setborder(HEIGHT + 1); 
	std::list<Platform*> Plat = map.getPlatforms();
	for(std::list<Platform*>::iterator it = Plat.begin(); it != Plat.end(); it++){
		Platform* platform = *it;
		if(platform->getx()-7 < ball.getx() && platform->getx() + platform->getw() > ball.getx()) //laa'ag
		{
			ball.setborder(platform->gety());
		}
	}

	std::list<Trap*> Tr = map.getTraps();
	for(std::list<Trap*>::iterator it = Tr.begin(); it != Tr.end(); it++){
		Trap* trap = *it;
		if(trap->getx() < ball.getx() && trap->getx() + trap->getw() > ball.getx()
			&& trap->gety() - trap->geth() < ball.gety() && trap->gety() > ball.gety())
			{
				std::cout<<Tr.size()<<"\n";
				std::cout<<map.getShapes().size();
				gameOver("trap");
				
			}
	}
	
	if(ball.gety() >= HEIGHT)
	{
		gameOver("deadline");
	}
}