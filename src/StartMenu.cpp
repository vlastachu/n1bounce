#include "StartMenu.h"
#include "Events.h"
#include "Engine.h"

void StartMenu::run()
{
	//mgr->setModule("game");
	//dynamic_cast<GameCore*>(mgr->getModule("game"))->getMap()->draw();
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(WIDTH*0.25f,HEIGHT*0.25f,WIDTH*0.5f,HEIGHT*0.5f);
	Font::findByName("std")->draw("start",WIDTH*0.35f,HEIGHT*0.4f, 64, 0, 0, 0);//TODO: find once and use pointer to draw
	//Graphics::outTextXY(WIDTH*0.35f,HEIGHT*0.4f,64,64,"start","dbg_font");
	if(Events::instance().kbdEvent==Events::RELEASE)
	{
		mgr->setModule("game");
	}
} 