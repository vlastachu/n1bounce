#include <iostream> // WTFFFFF??????????????

#include <GL\glut.h>
#include "Engine.h"
#include "Events.h"


void reshape(int Width,int Height)
{
	glViewport(0,0,Width,Height);
	Engine::Instance().reshape((float)Width,(float)Height);
}

void motion(int x,int y)
{
	Events::instance().onMove(x,y);
}

void mouse(int button, int state, int x, int y)
{
	if(button==0 && state==0)
	{
		Events::instance().onPress(x,y);
	}
	else if(button==0 && state==1)
	{
		Events::instance().onRelease(x,y);
	}
	//std::cout<<Events::instance()._event<<"\n";
}


void TimerFunction(int value)
{
	glutTimerFunc(30,TimerFunction, 1);
	
	Engine::Instance().play();Events::instance().onFrame();
    glutPostRedisplay();
    
}

void display()
{
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 1.0);
}


void keyPressed(int Key,int,int) 
{  
	Events::instance().onRelease(Key);
}

void keyReleased(int Key,int,int)
{
	
}



int main (int argc, char * argv[])
{
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(1024, 480);
	glutCreateWindow("Crysis");
	glOrtho (0, 1024, 480, 0, -1, 1);

	glutDisplayFunc(display);
	glutTimerFunc(30, TimerFunction, 1);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	glutReshapeFunc(reshape);
	
	Engine::Instance();

	glutMainLoop();

	return 0;
}
 