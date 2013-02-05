#pragma once

class GraphicShape
{
protected:
	float x,y;
	float radian(float a);
	void circle(int X, int Y, int R);
public:
	GraphicShape();
	virtual void draw() = 0;
	virtual void keyPressed (unsigned char key)=0;
	float getx();
	float gety();
	virtual ~GraphicShape();
};
