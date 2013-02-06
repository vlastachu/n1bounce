#include <iostream>
#include "defs.h"
#include "GameCore.h"
#include "Map.h"
#include "Ball.h"
#include "EventManager.h"
GameCore::GameCore()
{
}

void GameCore::Init()
{
	//e_mgr.Add(&ball);
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
	std::list<FixedMapShape*> Plat = g_map.getPlatforms();
	for(std::list<FixedMapShape*>::iterator it = Plat.begin(); it != Plat.end(); it++){
		FixedMapShape* platform = *it;
		if(platform->getx()-7 < ball.getx() && platform->getx() + platform->getw() > ball.getx()) //laa'ag
		{
			ball.setborder(platform->gety());
		}
	}

	std::list<FixedMapShape*> Tr = g_map.getTraps();
	for(std::list<FixedMapShape*>::iterator it = Tr.begin(); it != Tr.end(); it++){
		FixedMapShape* trap = *it;
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