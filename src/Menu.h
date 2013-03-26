#pragma once
#include "Module.h"
#include "Graphics.h"
#include "GUI.h"


class Menu: public Module
{
private:
	int currentButton;
	bool _key;
public:

	Menu(){}
	static void tourn(Button* b);
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();	
	virtual void keyPressed(int Key);
	virtual void send(map<string, void*> params);
};