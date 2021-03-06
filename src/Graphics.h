#pragma once
#include <map>
#include <string>
using std::string;
using std::map;


/*
Contains OpenGL texture id and info about location in the texture;
Initialization should be ONLY in Graphics::loadAtlas(name).
ffuuu. ������ ����� ��������� ����� � Graphics private  
���� ������������ ������ ������ Graphics::draw. ������� �� �����,
��� ����� �������� ����� ���� ��� � ����� ������ ��� �������� ����.
USAGE EXAMPLE:
Texture* chain = Texture::findByName("chain");
...
void draw(){
	chain->draw(root->toX(x),_y,root->toL(HEIGHT*0.07f),root->toL(HEIGHT*0.07f),0.5f,0,0);
}
*/
class Texture
{
protected:
	unsigned atlasId;
	float posX, posY, width, height, shiftX, shiftY;
	int pxWidth, pxHeight;
	static map<string, Texture*> textures;
	string name;
	void drawInner(float x, float y, float width, float height, float x0, float y0, float rot, int xOffset, int yOffset, float innerWidth, float innerHeight);
	Texture(){}
public:
	Texture(unsigned AtlasId, string Name, int AtlasHeight, int AtlasWidth, int PosX, int PosY, int Width, int Height, int ShiftX, int ShiftY);
	static Texture* findByName(string Name);
	/*
		x0 and y0 - coordinates of translation before rotation. 
		rot - rotation in degrees
	*/
	void draw(float x, float y, float width, float height, float x0, float y0, float rot);
};

/*
	Similiar to Texture class but also parse font files
	and draw chars from inner texture region
	font file should be located in data/font folder
	file name format: font~lucide.fnt, font~lucide.png 
	(important to use the same name in png file)
	USAGE EXAMPLE:
	Font* lucide = Font::findByName("lucide");
	...
	lucide->draw(...);
*/
class Font: public Texture
{
public: //lol
	struct Char
	{
		unsigned x, y, width, height, xoffset, yoffset, xadvance;
	};
private:
	map<char, Char*> chars;
	static map<string, Font*> fonts;
	unsigned fontSize;//xNum,yNum,startChar;
	/*
		USE: for draw string only
		RETURN: the char width to offset next char
		TODO: unhandled behavior on space (' ') typing
	*/
	float draw(char c,float x, float y, float height, float x0, float y0, float rot);
public:
	Font(unsigned AtlasId, string Name, int AtlasHeight, int AtlasWidth, int PosX, int PosY, int Width, int Height, int ShiftX, int ShiftY, string fontFileName);
	/*
		INPUT: file name without folder, prefix and extension
		for example file "font~lucide.fnt":
		Font::findByName("lucide");
	*/
	static Font* findByName(string Name);
	void pushChar(char cName, Char* ch);
	/*
		x0 and y0 - coordinates of translation before rotation. 
		rot - rotation in degrees
	*/
	void draw(string str,float x, float y, float height, float x0, float y0, float rot);
};

class Graphics
{
	static map<string,unsigned> textures;
	static map<string,Font> fonts;

	//static void outCharXY(float X,float Y,float W,float H,char C,string FontName);

public:
	static float radian(float a);
	//deprecated
	static void addTexture(unsigned TextureId,string TextureName);
	//static void addFont(unsigned TextureId,int XNum,int YNum,int StartChar,string FontName);

	//static void outTextXY(float X,float Y,float CharW,float CharH,const char* Str,string FontName);

	static unsigned png2tex(const char* name);
	static void draw(float X1,float Y1,float X2,float Y2,float X,float Y,float W,float H,
		  float X0,float Y0,float Rot,string Texture);
	/*
		USE: if you want to load textures.
		INPUT: the "*.atlas" file generated by cheetah from "../data/atlas" folder.
		the input string should be without folder and extension
	*/
	static void loadAtlas(string fileName);
	/*
		log used just for notificate developer
	*/
	static void log(string str);
	/*
		put log if condition is true;
		warning: this log used for errors, so if condition is true
		then program execution stopping and waiting user answer (y/n).
	*/
	static void logIf(bool condition, string str);
	static void circle(float X, float Y, float R);
	static void rectangle(float X,float Y,float W,float H);
	static void color(float R,float G,float B);
	static void line(float X1,float Y1,float X2,float Y2);
};