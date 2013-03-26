#include "Engine.h"
Engine::Engine()
{
	Graphics::addTexture(Graphics::png2tex("../data/ninja.png"),  "n_body");
	Graphics::addTexture(Graphics::png2tex("../data/leg.png"),    "n_leg");
	Graphics::addTexture(Graphics::png2tex("../data/katana.png"), "n_katana");
	Graphics::addTexture(Graphics::png2tex("../data/db.png"), "db");

	//Text::addFontStyle("gameinfo","../fonts/Ubuntu-m.ttf",63,0,0,0,0.005,false,Color4f(0.3,0,0,1),0,0,Color4f(0,0,0,1),0.0005,Color4f(0.75,0.75,0.75,1));
	Graphics::addFont("../fonts/Ubuntu-m.ttf");
	/*
	add background?
	Background
	*/

	mgr=new ModuleManager();
	game=new GameCore();
	pause=new Pause();
	
	mgr->Register("game",game);
	mgr->Register("pause",pause);
	mgr->setModule("game");
	game->Init();
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

void Engine::mouse(int button, int state, int x, int y)
{
	mgr->getActiveModule()->mouse(button, state, x, y);
}
void Engine::mousePasive(int x, int y)
{
	mgr->getActiveModule()->mousePasive(x, y);
}