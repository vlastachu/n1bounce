#pragma once
class Events
{
	Events();
public:	
	int key;
	int length;
	bool pressed;
	bool released;
	bool keyReleased;

	static const int border=5;

	float x,y;
	enum
	{
		NONE,CLICK,PRESS,RELEASE,HOLD
	}mouseEvent,kbdEvent;

	static Events& instance();
	void onFrame();
	void onPress(float X,float Y);
	void onRelease(float X,float Y);
	void onMove(float X,float Y);
	void onRelease(int Key);

	void reset();
};