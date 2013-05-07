#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <wchar.h>
#include <ft2build.h>
#include <limits>
#include FT_FREETYPE_H

FT_Library ft;	
FT_Face face;
const char *fontfilename = "C:/Users/vlastachu/Documents/Carrington.ttf";
GLuint      texture[10];  
		float PI = 3.1415926;

GLint uniform_mytexture;
int setup() { 
	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "Could not init freetype library\n");
		return 0;
	}
	if (FT_New_Face(ft, fontfilename, 0, &face)) {
		fprintf(stderr, "Could not open font %s\n", fontfilename);
		return 0;
	}
	FT_Set_Pixel_Sizes(face, 0, 63);
	return 1;
 }

struct Color4f
{
	float red,green, blue, alpha;
	Color4f(float r, float g, float b, float a):red(r),green(g),blue(b),alpha(a){}
	Color4f():red(0),green(0),blue(0),alpha(0){}
};

void color(Color4f c)
{
	glColor4f(c.red,c.green,c.blue,c.alpha);
}

Color4f mixColors(Color4f a, Color4f b, float mix)
{
	return Color4f(a.red*mix + b.red*(1-mix),a.green*mix + b.green*(1-mix),a.blue*mix + b.blue*(1-mix),a.alpha*mix + b.alpha*(1-mix));
}

Color4f addColor(Color4f a, Color4f b, float mix)
{
		return Color4f(a.red*mix + a.red*b.red*(1-mix),a.green*mix + a.green*b.green*(1-mix),a.blue*mix + a.blue*b.blue*(1-mix),a.alpha*mix + a.alpha*b.alpha*(1-mix));
}

int strSize;
GLuint tex;
void makeTexture(){
	glGenTextures(1,&tex);
	glBindTexture(GL_TEXTURE_2D,tex);
	std::string s = "Sed ut perspiciatis unde omnis iste natus sit voluptatem accusantiu";
	
	strSize = s.size();
	unsigned char *data = new unsigned char[strSize*128*4096];
	for(int i = 0; i < strSize*128*4096;i++) data[i] = 0;
	int left = 0; 
	FT_GlyphSlot g;
		  FT_Vector  delta;
    for(int i = 0; i < strSize; i++){
		
		FT_Load_Char( face, s[i], FT_LOAD_RENDER );
		g = face->glyph;
		if ( i > 0 )
		{
		  FT_Get_Kerning( face, s[i-1], s[i],
						  FT_KERNING_DEFAULT, &delta );
		  left += delta.x >> 6;
		}
		int pitch = g->bitmap.pitch;
		if (pitch < 0) pitch = -pitch;
		if(s[i] == ' ') left += 20; else
		for (int row = 0; row < g->bitmap.rows; ++row) {
			
				for(int b = 0; b < pitch; b++){
					if(data[left + 64*(strSize*(row + 64 -  g->bitmap_top)) + b] + g->bitmap.buffer[pitch * row + b] < UCHAR_MAX)
						data[left + 64*(strSize*(row + 64 -  g->bitmap_top)) + b] += g->bitmap.buffer[pitch * row + b];
					else
						data[left + 64*(strSize*(row + 64 -  g->bitmap_top)) + b] = UCHAR_MAX;
				}
		}
		left += g->advance.x >> 6;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glColor4f(0.2,0.4,0.8,1.);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	gluBuild2DMipmaps(
    GL_TEXTURE_2D, 
    GL_RGBA, 
    64*strSize, 
    128, 
    GL_ALPHA, 
    GL_UNSIGNED_BYTE, 
    data
);
	glDisable(GL_TEXTURE_2D);
}

class Fire{
private:

public:
	static void drawRainbow(Color4f a, Color4f b,float x, float y, float r, float R, float rot)
	{
		float dx,dy;
		glBegin(GL_TRIANGLE_STRIP);
				for(float i = rot-PI; i <= rot; i+=PI/36)
				{
					color(mixColors(mixColors(a,b,i/(-PI)),Color4f(0,0,0,1),1));
					dx = r*cos(i), dy = r*sin(i)*0.7;
					glVertex2f(x + dx, y + dy);
					color(mixColors(a,b,i/(-PI)));
					dx = R*cos(i), dy = R*sin(i)*0.7;
					glVertex2f(x + dx, y + dy);
				}
			glEnd();
	}
	static void draw(Color4f a, Color4f b,float x, float y, float r,float rot)
	{
		drawRainbow(mixColors(a,Color4f(1,0,0,1),0.5),mixColors(b,Color4f(1,0,0,1),0.5),x,y,r*3,r*4,rot);
		drawRainbow(mixColors(a,Color4f(1,1,0,1),0.5),mixColors(b,Color4f(1,1,0,1),0.5),x,y,r*2,r*3,rot);
		drawRainbow(mixColors(a,Color4f(0,0,0,1),0.5),mixColors(b,Color4f(0,0,0,1),0.5),x,y,r,r*2,rot);
		drawRainbow(mixColors(a,Color4f(1,0,0,1),0.5),mixColors(a,Color4f(1,0,0,1),0.5),x,y,0,r,rot);
	}
};

void display()
{
	glClearColor(1.0 ,1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		float dx = 0.9, dy = 0.9, outline = 4,x = 20, y = 10, w = 32*85, h = 64;
	   glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glColor4f(0,0,0,1);
		glBegin(GL_QUADS);
		float detalization = 64;float PI = 22.0/7.0;
			for(float i = 0.0; i <= PI*2; i += PI*2/detalization)
			{
				dx = outline*cos(i), dy = outline*sin(i);
		  glTexCoord2f(0.0f, 0.0f);glVertex2f(x+dx,y+dy); //top left
		  glTexCoord2f(1.0f, 0.0f);glVertex2f(x+dx + w,y+dy); //top right
		  glTexCoord2f(1.0f, 1.0f);glVertex2f(x+dx + w,y+dy + h); // bottom right
		  glTexCoord2f(0.0f, 1.0f);glVertex2f(x+dx ,y+dy + h); //bottom left
			}
		glEnd();
	glBindTexture(GL_TEXTURE_2D,tex);

		glBegin(GL_QUADS); 
		  glColor4f(0.9,0.0,0,1.);
		  glTexCoord2f(0.0f, 0.0f);glVertex2f(x,y); //top left
		  glTexCoord2f(1.0f, 0.0f);glVertex2f(x + w,y); //top right
		  glColor4f(0.9,0.9,0,1.);
		  glTexCoord2f(1.0f, 1.0f);glVertex2f(x + w,y + h); // bottom right
		  glTexCoord2f(0.0f, 1.0f);glVertex2f(x ,y + h); //bottom left
		glEnd();
	glDisable(GL_TEXTURE_2D);
	Color4f cur = Color4f(1,1,0.5,1);
	Color4f prev = cur;
	float width, left = 100;
	for(int i =1; i <30;i++)
	{
		if(i<20) cur = mixColors(cur,Color4f(1,0,0,1),0.94);
		else cur = mixColors(cur,Color4f(0,0,0,1),0.8);
		width = 12.0-12.0/(1+0.07*i);
		left += width*3; 
		Fire::draw(cur,prev,left,200,width,PI*(i%2));
		prev = cur;
	}
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
    
 // glUniform1i(uniform_mytexture, /*GL_TEXTURE*/0);
    glutPostRedisplay();
	glutSwapBuffers();
}
void TimerFunction(int value)
{

    
}
int main(int argc, char *argv[])
{
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       glutInitWindowSize(800,600);
       glutCreateWindow("Hello World");
		//glutTimerFunc(30, TimerFunction, 1);
	   glewInit();
	   glEnable (GL_TEXTURE_2D);
	   glEnable (GL_BLEND);
	glOrtho (0, 800, 600, 0, -1, 1);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

       setup();
	   makeTexture();
	   glutDisplayFunc(display);

       glutMainLoop();

       return 0;
}