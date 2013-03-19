#include "Menu.h"
#include "Graphics.h"
#include <GL\glut.h>
#include "Engine.h"
void Menu::keyReleased(int Key)
{
		
}
void Menu::tourn(Button* b)
{
	
		Engine::Instance().mgr.Stop("menu");
		Engine::Instance().mgr.Start("game");
}

void Menu::Init()
{
	EventManager::Instance().Register(this);
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
void Menu::mouse(int button, int state, int x, int y)
{
	float pointX = (float)x/glutGet(GLUT_WINDOW_WIDTH) * WIDTH;
    float pointY = ((float)y/(float)glutGet(GLUT_WINDOW_HEIGHT)) * HEIGHT;
	for(vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			(*i)->clickDown(pointX,pointY);
		}
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			(*i)->clickUp(pointX,pointY);
		}
	}		
}

void Menu::mousePasive(int x, int y)
{
	float pointX = (float)x/glutGet(GLUT_WINDOW_WIDTH) * WIDTH;
    float pointY = ((float)y/(float)glutGet(GLUT_WINDOW_HEIGHT)) * HEIGHT;
	for(vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->hover(pointX,pointY);
	}
}
void Menu::keyPressed(int Key)
{

}
void Menu::send(map<string, void*> params)
{

}