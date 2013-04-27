#include "StartMenu.h"
//#include "GameCore.h"
#include "Engine.h"

void StartMenu::run()
{std::cout<<"4";
	//mgr->setModule("game");
	//dynamic_cast<GameCore*>(mgr->getModule("game"))->getMap()->draw();
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(WIDTH*0.25f,HEIGHT*0.25f,WIDTH*0.5f,HEIGHT*0.5f);
	Graphics::outTextXY(WIDTH*0.35f,HEIGHT*0.4f,64,64,"start","dbg_font");
} 