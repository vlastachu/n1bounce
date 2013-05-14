#include "defs.h"
#include <GL/glu.h>
#include "lodepng.h"
#include "Graphics.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdarg>
void Graphics::color(float R,float G,float B)
{
	glColor3f(R,G,B);
}

void Graphics::circle(float X, float Y, float R)
{
	glBegin(GL_LINE_LOOP);
	for(float i=0;i<360;i+=5)
	{
		float a = radian(i);
		glVertex2f(cos(a)*R+X,sin(a)*R+Y);
	}
	glEnd();
}

void Graphics::rectangle(float X,float Y,float W,float H)
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(X,Y);
		glVertex2f(X+W,Y);
		glVertex2f(X+W,Y+H);
		glVertex2f(X,Y+H);
	glEnd();
}

void Graphics::line(float X1,float Y1,float X2,float Y2)
{
	glBegin(GL_LINE);
		glVertex2f(X1,Y1);
		glVertex2f(X2,Y2);
	glEnd();
}

float Graphics::radian(float a)
{
	return static_cast<float>(a / 180 * PI);
}
unsigned Graphics::png2tex(const char* name)
{
	unsigned char* data;
	unsigned width, height;
	unsigned texture;
	lodepng_decode32_file(&data, &width, &height, name);
	logIf(data == NULL, string("no such file ") + name);
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	/*glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	delete data;
	return texture;
}
void Graphics::draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture)
{
	map<string,unsigned>::iterator it=textures.find(Texture);
	if(it==textures.end()) return;
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, it->second);

	glPushMatrix();

	glRotatef(Rot, 0, 0, 1);
	glTranslatef((X)*cos(radian(Rot)) + (Y)*sin(radian(Rot)),
					(Y)*cos(radian(Rot)) - (X)*sin(radian(Rot)), 0);

	glColor3f(1.0,1.0,1.0);
	glBegin( GL_QUADS );
		glTexCoord2f(X1,Y1); glVertex2f(W*-X0,H*-Y0);
		glTexCoord2f(X1,Y2); glVertex2f(W*-X0,H*(1-Y0));
		glTexCoord2f(X2,Y2); glVertex2f(W*(1-X0),H*(1-Y0));
		glTexCoord2f(X2,Y1); glVertex2f(W*(1-X0),H*-Y0);
	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

map<string,Font> Graphics::fonts;
map<string,unsigned> Graphics::textures;

void Graphics::addTexture(unsigned TextureId,string TextureName)
{
	textures.insert(std::pair<string,unsigned>(TextureName,TextureId));
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}



	void Graphics::log(string str){
		//изначально я пытался воспользоваться многточием... но это кошмар
		std::cout << str << "\n";
	}

	void Graphics::logIf(bool condition, string str){
		if(condition){
			char q = 0;
			while(q != 'y'){
				log(str);
				std::cout << "do you want to continue? (y/n)";
				std::cin >> q;
				if(q == 'n') exit(0);
			}
		}
	}

	map<string, Texture*> Texture::textures;
	map<string, Font*> Font::fonts;

void Graphics::loadAtlas(string fileName){
	std::ifstream atlasFile("../data/atlas/" + fileName + ".atlas");
	logIf(!atlasFile.is_open(), "Graphics::loadAtlas no such file ../data/atlas/" + fileName + ".atlas");
	unsigned char* data;
	unsigned atlasW, atlasH;
	unsigned atlasId;
	lodepng_decode32_file(&data, &atlasW, &atlasH, ("../data/atlas/" + fileName + ".png").c_str());
	logIf(data == NULL, "Graphics::loadAtlas no such file ../data/atlas/" + fileName + ".png");
	glGenTextures(1,&atlasId);
	glBindTexture(GL_TEXTURE_2D,atlasId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, atlasW, atlasH, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete data;
	string out; 
	std::vector<string> str, fontStr;
	std::getline(atlasFile, out);
	while(std::getline(atlasFile, out)){
		str = split(out,'\t');
		if(split(str.at(0),'~').at(0) == "font"){
			Font* font = new Font(atlasId, split(split(str.at(0),'~').at(1),'.').at(0), atlasH, atlasW, atoi(str.at(1).c_str()),
				atoi(str.at(2).c_str()),atoi(str.at(3).c_str()), atoi(str.at(4).c_str()), atoi(str.at(5).c_str()), 
				atoi(str.at(6).c_str()),  "../data/font/" + split(str.at(0),'.').at(0) + ".fnt");
		}
		else 
			new Texture(atlasId, split(str.at(0),'.').at(0), atlasH, atlasW, atoi(str.at(1).c_str()), atoi(str.at(2).c_str()),atoi(str.at(3).c_str()), atoi(str.at(4).c_str()), atoi(str.at(5).c_str()), atoi(str.at(6).c_str()));
	}
	atlasFile.close();
}

	void Texture::drawInner(float x, float y, float width, float height, float x0, float y0, float rot, int xOffset, int yOffset, float innerWidth, float innerHeight){	
		float texX1 = this->posX + (xOffset/(float)pxWidth)*this->width;
		float texY1 = this->posY + (yOffset/(float)pxHeight)*this->height;
		float texX2 = texX1 + this->width*(innerWidth);
		float texY2 = texY1 + this->height*(innerHeight);
		x += shiftX;
		y += shiftY;
		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, atlasId);

		glPushMatrix();

		glRotatef(rot, 0, 0, 1);
		glTranslatef((x)*cos(Graphics::radian(rot)) + (y)*sin(Graphics::radian(rot)),
						(y)*cos(Graphics::radian(rot)) - (x)*sin(Graphics::radian(rot)), 0);

		glColor3f(1.0,1.0,1.0);
		glBegin( GL_QUADS );
			glTexCoord2f(texX1, texY1); glVertex2f(width*-x0,height*-y0);
			glTexCoord2f(texX1, texY2); glVertex2f(width*-x0,height*(1-y0));
			glTexCoord2f(texX2, texY2); glVertex2f(width*(1-x0),height*(1-y0));
			glTexCoord2f(texX2, texY1); glVertex2f(width*(1-x0),height*-y0);
		glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}

	Texture::Texture(unsigned AtlasId, string Name, int AtlasHeight, int AtlasWidth, int PosX, int PosY, int Width, int Height, int ShiftX, int ShiftY){
		atlasId = AtlasId;
		name = Name;
		posX = PosX/(float)AtlasWidth;
		posY = PosY/(float)AtlasHeight;
		width = Width/(float)AtlasWidth;
		height = Height/(float)AtlasHeight;
		pxWidth = Width;
		pxHeight = Height;
		shiftX = ShiftX/(float)AtlasWidth;
		shiftY = ShiftY/(float)AtlasHeight;
		textures.insert(std::pair<string, Texture*>(Name, this));
	}

	Texture* Texture::findByName(string Name){
		map<string, Texture*>::iterator it = textures.find(Name);
		Graphics::logIf(it == textures.end(), "Texture::findByName texture not found:" + Name);
		return it->second;
	}

	void Texture::draw(float x, float y, float width, float height, float x0, float y0, float rot){	
		drawInner(x,y,width, height, x0, y0, rot, 0, 0, 1, 1);
	}

	
	Font::Font(unsigned AtlasId, string Name, int AtlasHeight, int AtlasWidth, int PosX, int PosY, int Width, int Height, int ShiftX, int ShiftY, string fontFileName){
		std::ifstream text; 
		string out;
		std::vector<string> str;
		atlasId = AtlasId;
		name = Name;
		posX = PosX/(float)AtlasWidth;
		posY = PosY/(float)AtlasHeight;
		width = Width/(float)AtlasWidth;
		height = Height/(float)AtlasHeight;
		pxWidth = Width;
		pxHeight = Height;
		shiftX = ShiftX/(float)AtlasWidth;
		shiftY = ShiftY/(float)AtlasHeight;
		fonts.insert(std::pair<string, Font*>(Name, this));
		text.open(fontFileName);
		Graphics::logIf(!text.is_open(), "Font::Font no such file " + fontFileName);
		std::getline(text, out);
		std::vector<string> title = split(out, ' ');
		string strFontSize;
		for(std::vector<string>::iterator it = title.begin(); it != title.end(); it++)
			if(split(*it, '=').at(0) == "size"){
				strFontSize = split(*it, '=').at(1);
				break;
			}
		fontSize = atoi(strFontSize.c_str());
		while(std::getline(text, out)){
			str = split(out, ' ');
			//M-M-MAXIMUM BYDLOCODE
			//можно красивее распарсить конечно. ну или сделать функцию чтобы меньше копипасты было
			if(str.at(0) == "char"){
				Font::Char* t = new Font::Char();
				t->x = atoi(split(str.at(2),'=').at(1).c_str());
				t->y = atoi(split(str.at(3),'=').at(1).c_str());
				t->width = atoi(split(str.at(4),'=').at(1).c_str());
				t->height = atoi(split(str.at(5),'=').at(1).c_str());
				t->xoffset = atoi(split(str.at(6),'=').at(1).c_str());
				t->yoffset = atoi(split(str.at(7),'=').at(1).c_str());					
				this->pushChar(atoi(split(str.at(1),'=').at(1).c_str()), t);
			}
		}
		text.close();
		fonts.insert(std::pair<string, Font*>(fontFileName, this));
	}

	Font* Font::findByName(string Name){
		map<string, Font*>::iterator it = fonts.find(Name);
		Graphics::logIf(it == fonts.end(), "Font::findByName font not found");
		return it->second;
	}

	void Font::pushChar(char cName, Char* ch){
		chars.insert(std::pair<char, Char*>(cName, ch));
	}
	float Font::draw(char c,float x, float y, float height, float x0, float y0, float rot){
		if(c == ' ') return height;
		map<char, Char*>::iterator it = chars.find(c);
		Graphics::logIf(it == chars.end(), "Font::draw char not found");
		Char* ch = it->second;
		drawInner(x + ch->xoffset*height/fontSize, y + ch->yoffset*height/fontSize, ch->width*height/fontSize, ch->height*height/fontSize, x0, y0, rot, 
			ch->x, ch->y, (float)ch->width/(float)pxWidth, (float)ch->height/(float)pxHeight);
		return (ch->xoffset + ch->width + ch->xadvance + 1)*height/fontSize; // + somespace
	}
	void Font::draw(string str,float x, float y, float height, float x0, float y0, float rot){
		unsigned xOffset = 0;
		for(string::iterator i = str.begin(); i != str.end(); i++)
			xOffset += draw(*i, x + xOffset, y, height, x0, y0, rot);
	}
//void Graphics::outCharXY(float X,float Y,float W,float H,char C,string FontName)
//{
//	map<string,Font>::iterator it=fonts.find(FontName);
//	if(it==fonts.end()) return;
//	float x1=((C-it->second.startChar)%it->second.xNum)/(float)it->second.xNum;
//	float y1=((C-it->second.startChar)/it->second.xNum)/(float)it->second.yNum;
//	float x2=x1+1/(float)it->second.xNum;
//	float y2=y1+1/(float)it->second.yNum;
//
//	glEnable( GL_TEXTURE_2D );
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBindTexture( GL_TEXTURE_2D, it->second.texture);
//
//	glColor3f(1.0,1.0,1.0);
//	glBegin( GL_QUADS );
//		glTexCoord2f(x1,y1); glVertex2f(X,Y);
//		glTexCoord2f(x1,y2); glVertex2f(X,Y+H);
//		glTexCoord2f(x2,y2); glVertex2f(X+W,Y+H);
//		glTexCoord2f(x2,y1); glVertex2f(X+W,Y);
//	glEnd();
//
//	glDisable(GL_BLEND);
//	glDisable(GL_TEXTURE_2D);
//
//	//draw(x1,y1,x2,y2,X,Y,W,H,0,0,0,it->second.texture);
//}
//
//void Graphics::outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName)
//{
//	for(int i=0;Str[i]!='\0';i++)
//		outCharXY(X+CharW*i,Y,CharW,CharH,Str[i],FontName);
//}
//
//void Graphics::addFont(unsigned TextureId,int XNum,int YNum,int StartChar,string FontName)
//{
//	fonts.insert(std::pair<string,Font>(FontName,Font(TextureId,XNum,YNum,StartChar)));
//}
























