#include "Pause.h"
#include "GameCore.h"
void Pause::Run()
{
	dynamic_cast<GameCore*>(mgr->getModule("game"))->getMap()->draw();
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(WIDTH*0.25,HEIGHT*0.25,WIDTH*0.5,HEIGHT*0.5);
	//Text::draw("Pause",0.35,0.4,"headline");
}