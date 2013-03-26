#pragma once
#include "ModuleManager.h"
#include "Graphics.h"
#include "GUI.h"
#include <vector>
#include <GL\glut.h>
using std::vector;
class ModuleManager;
class Module
{
protected:
	ModuleManager* mgr;
	vector<Button*> buttons;
public:
	void setManager(ModuleManager* Mgr)
	{
		mgr=Mgr;
	}
	
	virtual void Init(){}
	virtual void Run(){}
	virtual void Clear(){}
	virtual void keyPressed(int Key){}
	virtual void keyReleased(int Key){}
	void mouse(int button, int state, int x, int y)
	{
		float pointX = (float)x/Graphics::getWindowWidth();
		float pointY = (float)y/Graphics::getWindowHeight();
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
	void mousePasive(int x, int y)
	{
	float pointX = (float)x/Graphics::getWindowWidth();
	float pointY = (float)y/Graphics::getWindowHeight();
	for(vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->hover(pointX,pointY);
	}
}
};