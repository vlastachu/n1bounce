#include "Engine.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"
#include <iostream>

Engine::Engine()
{
	mgr.Register("game",&game);
	mgr.Start("game");
}

Engine& Engine::Instance()
{
        static Engine theSingleInstance;
        return theSingleInstance;
}

void Engine::gameOver(char* also){
		std::cout << "GAME OVER! Try again." << also << "\n";
		mgr.Stop("game");
		mgr.Start("game");
}

void Engine::play()
{
	mgr.Run();
}