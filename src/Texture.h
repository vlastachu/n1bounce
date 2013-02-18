#pragma once
#include <vector>
#include "defs.h"

class Texture{
private:
	static std::vector<unsigned int> numbers;
	unsigned int number;
public:
	Texture();
	unsigned int getNumber();
	void setTexture();
	void getTexture();
	static int addToPowerOfTwo(int i);
};