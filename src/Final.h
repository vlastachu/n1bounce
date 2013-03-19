#pragma once
#include "Module.h"
#include "Text.h"
#include "GUI.h"
class Final: public Module
{
private:
	Text *postScriptum, *bestResult, *yourResult, *buttonR; 
	Button *menuButton, *againButton;
	int best, your;
	bool _key;
	static void toMenu(Button *b);
	static void toGame(Button *b);

public:

	Final();
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();	
	virtual void keyPressed(int Key);
	virtual void send(map<string, void*> params);
};