#include "Events.h"

Events::Events()
{
	mouseEvent=NONE;
	kbdEvent=NONE;
}


Events& Events::instance()
{
	static Events theSingleInstance;
	return theSingleInstance;
}

void Events::reset()
{
	pressed=false;
	released=false;
	length=0;
	mouseEvent=NONE;
}

void Events::onFrame()
{
	if(keyReleased)
	{
		kbdEvent=RELEASE;
		keyReleased=false;
	}
	else
	{
		kbdEvent=NONE;
	}

	if(pressed)
	{
		length++;
		if(!released)
		{
			if(length==border)
			{
				mouseEvent=PRESS;
			}
			else if(length>border)
			{
				mouseEvent=HOLD;
			}
			else
			{
				mouseEvent=NONE;
			}
		}
		else
		{
			if(length>border)
			{
				mouseEvent=RELEASE;
			}
			else
			{
				mouseEvent=CLICK;
			}
			pressed=false;
			released=false;
			length=0;
		}
	}
	else
	{
		mouseEvent=NONE;
	}
}

void Events::onPress(float X,float Y)
{
	x=X,y=Y;
	pressed=true;
}

void Events::onRelease(float X,float Y)
{
	x=X;y=Y;
	released=true;
}

void Events::onMove(float X,float Y)
{
	x=X;y=Y;
}

void Events::onRelease(int Key)
{
	key=Key;
	keyReleased=true;
}