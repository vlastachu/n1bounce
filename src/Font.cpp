//#include <stdio.h>
#include <GL\glu.h>
#include "Font.h"
#include "lodepng.h"



Font::Font(const char* Name,int XNum,int YNum,int StartChar)
{
	unsigned char* data;
		
	lodepng_decode32_file(&data, &width, &height, Name);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	delete data;

	xNum=XNum;
	yNum=YNum;
	startChar=StartChar;
	//printf("%d  %d  %u\n",width,height,texture);
}
void Font::outTextXY(const char* Text,float X,float Y,float Scale)
{
	for(int i=0;Text[i]!='\0';i++)
	{
		glColor3f(1.0 ,1.0, 1.0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture( GL_TEXTURE_2D, texture);

		float x1=((Text[i]-startChar)%xNum)/(float)xNum;
		float y1=((Text[i]-startChar)/xNum)/(float)yNum;
		float x2=x1+1/(float)xNum;
		float y2=y1+1/(float)yNum;
		
		float X1=X+(i*width/xNum)*Scale;
		float Y1=Y;
		float X2=X+((i+1)*width/xNum)*Scale;
		float Y2=Y+(height/yNum)*Scale;
		
		glBegin( GL_QUADS );
			glTexCoord2f(x1,y1); glVertex2f(X1,Y1);
			glTexCoord2f(x1,y2); glVertex2f(X1,Y2);
      
			glTexCoord2f(x2,y2); glVertex2f(X2,Y2);
			glTexCoord2f(x2,y1); glVertex2f(X2,Y1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
}