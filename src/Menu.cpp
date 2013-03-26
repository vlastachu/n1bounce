#include "Menu.h"
#include "Graphics.h"
#include <GL\glut.h>
#include "Engine.h"
void Menu::keyReleased(int Key)
{
		
}
void Menu::tourn(Button* b)
{
	Engine::Instance().mgr->setModule("game");
}

void Menu::Init()
{
	currentButton = 0;
	buttons.push_back((new Button("Tournament", 100, 50))->setOnClick(tourn));
	buttons.push_back(new Button("Campaign", 100, 140));
	buttons.push_back(new Button("Settings", 100, 230));
	buttons.push_back(new Button("Quit", 100, 320));

}
void Menu::Run()
{
 	for(int i = 0; i < 4; i++)
		buttons[i]->draw();

	//todo:hover
}



void Menu::keyPressed(int Key)
{

}
void Menu::send(map<string, void*> params)
{

}