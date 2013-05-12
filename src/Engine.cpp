#include "Engine.h"

Engine::Engine()
{
	w_width=1024;
	w_height=480;
	Graphics::loadAtlas("atlas");
	
	mgr=new ModuleManager();
	game=new GameCore();
	start=new StartMenu();
	g_over=new GameOver();
	
	mgr->registrate("game",game);
	mgr->registrate("start",start);
	mgr->registrate("g_over",g_over);
	mgr->setModule("start");
	//game->init();
}

Engine& Engine::Instance()
{
        static Engine theSingleInstance;
        return theSingleInstance;
}

void Engine::play()
{
	mgr->run();
}


void Engine::reshape(float Width, float Height)
{
	w_width=Width;
	w_height=Height;
}
