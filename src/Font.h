#pragma once
class Font
{
	unsigned texture;
	unsigned width,height;
	int xNum,yNum,startChar;
public:
	Font(const char* Name,int XNum,int YNum,int StartChar);
	void outTextXY(const char* Text,float X,float Y,float Scale);
};