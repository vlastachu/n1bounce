#pragma once
#include "Module.h"
#include "Text.h"

class Final: public Module
{
private:
	Text *postScriptum, *bestResult, *yourResult, *buttonR; 
	int best, your;
	bool _key;
public:

	Final();
	virtual void keyReleased(int Key);
	virtual void Init();
	virtual void Run();	
	virtual void keyPressed(int Key);
	virtual void send(map<string, void*> params);
};