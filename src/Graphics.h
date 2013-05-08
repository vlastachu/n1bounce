#pragma once
#include <map>
#include <string>
using std::string;
using std::map;

class Texture
{
protected:
	unsigned atlasId;
	float posX, posY, width, height, shiftX, shiftY;
	int pxWidth, pxHeight;
	static map<string, Texture*> textures;
	string name;
	void drawInner(float x, float y, float width, float height, float x0, float y0, float rot, int xOffset, int yOffset, int innerWidth, int innerHeight){	
		float texX1 = this->posX + (xOffset/(float)pxWidth);
		float texY1 = this->posY + (yOffset/(float)pxHeight);
		float texX2 = texX1 + this->width*(innerWidth/(float)pxWidth);
		float texY2 = texY1 + this->height*(innerHeight/(float)pxHeight);
		x += shiftX;
		y += shiftY;
		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, atlasId);

		glPushMatrix();

		glRotatef(rot, 0, 0, 1);
		glTranslatef((x)*cos(radian(rot)) + (y)*sin(radian(rot)),
						(y)*cos(radian(rot)) - (x)*sin(radian(rot)), 0);

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
public:
	Texture(unsigned AtlasId, string Name, int AtlasHeight, int AtlasWidth, int PosX, int PosY, int Width, int Height, int ShiftX, int ShiftY){
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

	static Texture* findByName(string Name){
		map<string, Texture*>::iterator it = textures.find(Name);
		if(it == textures.end())
			return NULL;
		else
			return it->second;
	}

	void draw(float x, float y, float width, float height, float x0, float y0, float rot){	
		drawInner(x,y,width, height, x0, y0, rot, 0, 0, 1, 1);
	}
};

class Font: public Texture
{
private:
	struct Char
	{
		unsigned x, y, width, height, xoffset, yoffset, xadvance;
	};
	map<char, Char*> chars;
	static map<string, Font*> fonts;
	unsigned fontSize;//xNum,yNum,startChar;
public:
	void setFontSize(unsigned FontSize){
		fontSize = FontSize;
	}
	static Font* findByName(string Name){
		map<string, Font*>::iterator it = fonts.find(Name);
		if(it == fonts.end())
			return NULL;
		else
			return it->second;
	}
	void pushChar(char cName, Char* ch){
		chars.insert(std::pair<char, Char*>(cName, ch));
	}

};

class Graphics
{
	static map<string,unsigned> textures;
	static map<string,Font> fonts;

	static float radian(float a);
	static void outCharXY(float X,float Y,float W,float H,char C,string FontName);

public:
	static void addTexture(unsigned TextureId,string TextureName);
	static void addFont(unsigned TextureId,int XNum,int YNum,int StartChar,string FontName);

	static void outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName);

	static unsigned png2tex(const char* name);
	static void draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture);
	
	static void Graphics::loadAtlas(string fileName);
	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
	static void color(float R,float G,float B);
	static void line(float X1,float Y1,float X2,float Y2);
};