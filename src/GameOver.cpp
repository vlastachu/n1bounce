#include "GameOver.h"
#include "GameCore.h"
#include "Engine.h"

void GameOver::run()
{

	char chScore[10];
	_itoa_s(score,chScore,10);

	//mgr->setModule("game");
	//dynamic_cast<GameCore*>(mgr->getModule("game"))->getMap()->draw();
	Graphics::color(0.5,0.5,0.5);
	Graphics::rectangle(WIDTH*0.25f,HEIGHT*0.25f,WIDTH*0.5f,HEIGHT*0.5f);
	Graphics::outTextXY(WIDTH*0.35f,HEIGHT*0.4f,64,64,"GameOver","dbg_font");
	Graphics::outTextXY(WIDTH*0.35f,HEIGHT*0.5f,64,64,chScore,"dbg_font");
} 
void GameOver::init(Module* Sender)
{
	GameCore* temp=dynamic_cast<GameCore*>(Sender);
	if(temp)
	{
		score=temp->score;
	}
}