#include "Engine.h"

Engine::Engine()
{
	w_width=1024;
	w_height=480;

	Graphics::addTexture(Graphics::png2tex("../data/ninja.png"),  "n_body");
	Graphics::addTexture(Graphics::png2tex("../data/leg.png"),    "n_leg");
	Graphics::addTexture(Graphics::png2tex("../data/katana.png"), "n_katana");
	Graphics::addTexture(Graphics::png2tex("../data/db.png"), "db");
	Graphics::addTexture(Graphics::png2tex("../data/chain.png"), "chain");
	Graphics::addTexture(Graphics::png2tex("../data/trap.png"), "trap");


	Graphics::addFont(Graphics::png2tex("../data/font.png"),16,16,0,"dbg_font");

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
