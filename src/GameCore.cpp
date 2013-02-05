#include "GameCore.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"
#include <iostream>
#include "EventManager.h"
GameCore::GameCore()
{
}

void GameCore::Init()
{
	e_mgr.Add(&ball);
	g_map.init();
	ball.init();
}

void GameCore::Clear()
{
	g_map.clear();
}

void GameCore::gameOver(char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		g_map.clear();
		g_map.init();
		ball.init();
}

void GameCore::Run()
{
	g_map.move();
	g_map.draw();
	ball.move();
	ball.draw();

	ball.setborder(HEIGHT + 1); 
	std::list<Platform*> Plat = g_map.getPlatforms();
	for(std::list<Platform*>::iterator it = Plat.begin(); it != Plat.end(); it++){
		Platform* platform = *it;
		if(platform->getx()-7 < ball.getx() && platform->getx() + platform->getw() > ball.getx()) //laa'ag
		{
			ball.setborder(platform->gety());
		}
	}

	std::list<Trap*> Tr = g_map.getTraps();
	for(std::list<Trap*>::iterator it = Tr.begin(); it != Tr.end(); it++){
		Trap* trap = *it;
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