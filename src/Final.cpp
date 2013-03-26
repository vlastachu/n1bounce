
#include "Final.h"
#include "Engine.h"
#include <sstream>

void Final::Init(){
	std::stringstream ssBest; ssBest << "High score " << best;
	std::stringstream ssYour; ssYour << "Your result " << your;
	sBest = ssBest.str();
	sYour = ssYour.str();
	menuButton = (new Button("menu", 200, 480))->setOnClick(toMenu);
	againButton = (new Button("try again", 550, 480))->setOnClick(toGame);
	buttons.push_back(menuButton);
	buttons.push_back(againButton);
}
void Final::toMenu(Button* b){
	
	Engine::Instance().mgr->setModule("menu");
}
void Final::toGame(Button* b){
	
	Engine::Instance().mgr->setModule("game");
}

void Final::send(map<string, void*> params){
	map<string, void*>::iterator it = params.find("score");
	if(it !=params.end()){
		your = *((int*)it->second);
		if(best < your) best = your;
	}
}
Final::Final(){
	best = 0;
}

void Final::Run(){
	glClearColor(1.0 ,1.0, 1.0, 0.7);
	glClear(GL_COLOR_BUFFER_BIT);
	//Text::draw("GAME OVER",0.45,0.3,"headline");
	//Text::draw(sBest,0.45,0.4,"info");
	//Text::draw(sYour,0.45,0.45,"info");

	againButton->draw();
	menuButton->draw();
}

void Final::keyPressed(int key){
	if (!_key && key == GLUT_KEY_UP){
		/*Engine::Instance().mgr.Stop("final");
		Engine::Instance().mgr.Start("game");*/
	}
}

void Final::keyReleased(int Key)
{
	_key=false;
}