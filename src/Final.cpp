#include "Text.h"
#include <GL\glut.h>
#include "Final.h"
#include "Engine.h"
#include <sstream>

void Final::Init(){
	EventManager::Instance().Register(this);
	std::stringstream sBest; sBest << "High score " << best;
	std::stringstream sYour; sYour << "Your result " << your;
	
	menuButton = (new Button("menu", 200, 480))->setOnClick(toMenu);
	againButton = (new Button("try again", 550, 480))->setOnClick(toGame);
	buttons.push_back(menuButton);
	buttons.push_back(againButton);
	postScriptum = (new Text)
		->setFont("../fonts/Ubuntu-b.ttf",63)
		->setText("ninja died")
		->setX(350)
		->setKerning(true)
		->setY(90)
		->setColor(0.7,0.1,0.1,1.0)
		->setOutline(2,0.5,0.1,0.3,1);
	bestResult  = (new Text)
		->setFont("../fonts/Ubuntu-b.ttf",33)
		->setText(sBest.str())
		->setX(370)
		->setY(220)
		->setColor(0.4,0.5,0.7,1.0)->setOutline(2,0.1,0.1,0.4,1);
	yourResult = (new Text)
		->setFont("../fonts/Ubuntu-b.ttf",33)
		->setText(sYour.str())
		->setX(370)
		->setY(260)
		->setColor(0.4,0.5,0.7,1.0)->setOutline(2,0.1,0.1,0.4,1);
  /* buttonR = (new Text)
		->setFont("../fonts/Ubuntu-m.ttf",42)
		->setText("Press UP to try again")
		->setX(300)
		->setY(480)
		->setColor(0.9,0.5,0.4,1.0);*/

}
void Final::toMenu(Button* b){

		Engine::Instance().mgr.Stop("final");
		Engine::Instance().mgr.Start("menu");
}
void Final::toGame(Button* b){

		Engine::Instance().mgr.Stop("final");
		Engine::Instance().mgr.Start("game");
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
	postScriptum->draw();
	bestResult->draw();
	yourResult->draw();
	againButton->draw();
	menuButton->draw();
}

void Final::keyPressed(int key){
	if (!_key && key == GLUT_KEY_UP){
		Engine::Instance().mgr.Stop("final");
		Engine::Instance().mgr.Start("game");
	}
}

void Final::keyReleased(int Key)
{
	_key=false;
}