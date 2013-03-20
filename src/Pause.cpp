#include "Pause.h"
#include "GameCore.h"
#include "Engine.h"
void Pause::Run()
{
	dynamic_cast<GameCore*>(mgr->getModule("game"))->getMap()->draw();
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(WIDTH*0.25,HEIGHT*0.25,WIDTH*0.5,HEIGHT*0.5);
	Engine::Instance().getFont()->outTextXY("Pause",WIDTH*0.35,HEIGHT*0.4,4);
	
}