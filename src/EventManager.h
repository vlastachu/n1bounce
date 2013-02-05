//#pragma once
#include <vector>
#include "GraphicShape.h"

class EventManager
{
	vector<GraphicShape*> listeners;
public:
	void Add(GraphicShape* GS)
	{
		listeners.push_back(GS);
	}
	void keyPressed (unsigned char key) 
	{  
		for(vector<GraphicShape*>::iterator it=listeners.begin();it!=listeners.end();it++)
		{
			(*it)->keyPressed(key);
		}
	}
};