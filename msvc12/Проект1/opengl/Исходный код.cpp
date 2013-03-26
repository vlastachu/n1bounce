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
	//FT_Load_Char( face, 'O', FT_LOAD_RENDER );
	//FT_GlyphSlot g = face->glyph;

	//glGenTextures(1, &texture[0]);    // Create The Texture
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D,  GL_RGBA, g->bitmap.width, g->bitmap.rows,  GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	return 1;
 }

//void PutIntoTexture( FT_Bitmap* bmp, byte* td, int x, int y, int maxX, int maxY )
//{
//  int x0, y0, x1, y1;
//  int x_max = x + bmp->width;
//  int y_max = y + bmp->rows;
//
//  if ( x_max >= maxX ) x_max = maxX;
//  if ( y_max >= maxY ) y_max = maxY;
//  if ( x < 0 ) x = 0;
//  if ( y < 0 ) y = 0;
//  int len = x_max - x;
//
//
//  for ( y0 = y, y1 = 0, x0 = y0*maxX, x1 = y1 * bmp->width; y0 < y_max; ++y0, ++y1, x0 += maxX, x1 += bmp->width )
//    memcpy( td+(x0+x), bmp->buffer+x1, len );
//}
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
			//std::memcpy(data + left + 64*(strSize*(row + 64 -  g->bitmap_top))
				//, g->bitmap.buffer + pitch * row, pitch);
		}
		left += g->advance.x >> 6;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Linear Filtering
	glColor4f(0.2,0.4,0.8,1.);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	/*glTexImage2D( GL_TEXTURE_2D, 
              0, 
              GL_RGBA, 
              1024, 
              128, 
              0,  
              GL_RED, 
              GL_UNSIGNED_BYTE, 
              data );*/
	gluBuild2DMipmaps(
    GL_TEXTURE_2D, 
    GL_RGBA, 
    64*strSize, 
    128, 
    GL_ALPHA, 
    GL_UNSIGNED_BYTE, 
    data
);
	
}
void display()
{
	glClearColor(1.0 ,1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    //glLoadIdentity();//load identity matrix
    	//glTexImage2D( GL_TEXTURE_2D, 
  //            0, 
  //            GL_RGBA, 
  //            g->bitmap.width, 
  //            g->bitmap.rows, 
  //            0,  
  //            GL_RED, 
  //            GL_UNSIGNED_BYTE, 
  //            g->bitmap.buffer );

//gluBuild2DMipmaps(
//    GL_TEXTURE_2D, 
//    GL_RGBA, 
//    64*strSize, 
//    64*strSize, 
//    GL_RED, 
//    GL_UNSIGNED_BYTE, 
//    data
//);

		float dx = 0.9, dy = 0.9, outline = 5,x = 20, y = 10, w = 32*85, h = 64;
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
	int i = 4%4;
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