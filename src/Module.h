#pragma once
#include "GUI.h"
#include <map>
#include <vector>
#include <string>
#include <GL\glut.h>
//using namespace std;
using std::string;
using std::map;
using std::vector;
#include "ModuleManager.h"
#include "defs.h"
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
	void mousePasive(int x, int y)
	{
	float pointX = (float)x/glutGet(GLUT_WINDOW_WIDTH) * WIDTH;
    float pointY = ((float)y/(float)glutGet(GLUT_WINDOW_HEIGHT)) * HEIGHT;
	for(vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
	{
		(*i)->hover(pointX,pointY);
	}
}
	virtual void send(map<string, void*> params){}
};