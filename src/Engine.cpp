#include "Engine.h"

Engine::Engine()
{
	mgr=new ModuleManager();
	game=new GameCore();
	pause=new Pause();
	font=new Font("../data/font.png",16,16,0);
	mgr->Register("game",game);
	mgr->Register("pause",pause);
	mgr->setModule("game",true);
}

Engine& Engine::Instance()
{
        static Engine theSingleInstance;
        return theSingleInstance;
}

void Engine::play()
{
	mgr->Run();
}

void Engine::keyPressed(int Key)
{
	mgr->getActiveModule()->keyPressed(Key);
}

void Engine::keyReleased(int Key)
{
	mgr->getActiveModule()->keyReleased(Key);
}