#include "Engine.h"

Engine::Engine()
{
	Graphics::addTexture(Graphics::png2tex("../data/ninja.png"),  "n_body");
	Graphics::addTexture(Graphics::png2tex("../data/leg.png"),    "n_leg");
	Graphics::addTexture(Graphics::png2tex("../data/katana.png"), "n_katana");
	Graphics::addTexture(Graphics::png2tex("../data/db.png"), "db");
	Graphics::addTexture(Graphics::png2tex("../data/chain.png"), "chain");
	Graphics::addTexture(Graphics::png2tex("../data/trap.png"), "trap");


	Graphics::addFont(Graphics::png2tex("../data/font.png"),16,16,0,"dbg_font");

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