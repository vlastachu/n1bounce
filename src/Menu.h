#pragma once
#include "Module.h"
#include "Text.h"
#include "Graphics.h"
#include "GUI.h"


class Menu: public Module
{
private:
	int currentButton;
	vector<Button*> buttons;//campaign, *tournament, *options, *exit; 
	bool _key;
public:

	Menu(){}
	virtual void mouse(int button, int state, int x, int y);
	virtual void mousePasive(int x, int y);
	static void tourn(Button* b);
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();	
	virtual void keyPressed(int Key);
	virtual void send(map<string, void*> params);
};