#include "Texture.h"
std::vector<unsigned int> Texture::numbers;

Texture::Texture(){
	glGenTextures(1,&number);
	numbers.push_back(number);
}

unsigned int Texture::getNumber(){
	return number;
}

void Texture::setTexture(){
	glBindTexture(GL_TEXTURE_2D,number);
}

void Texture::getTexture(){
	glBindTexture(GL_TEXTURE_2D,number);
}

int Texture::addToPowerOfTwo(int i){
	int j = 1;
	while (j < i) 
		j = j << 1;
	return j;
}