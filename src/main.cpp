#include <vector>
#include <time.h>
#include <iostream>
using namespace std;
#include <GL\glut.h>
#include "Engine.h"
#include "EventManager.h"
#include "defs.h"







void reshape(int w, int h)
{
}

void motion(int X,int Y)
{
}

void mouse(int button, int state, int x, int y)
{
}


void TimerFunction(int value)
{
	glutTimerFunc(30,TimerFunction, 1);
	Engine::Instance().play();
    glutPostRedisplay();
    
}

void display()
{
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 1.0);
}


void keyPressed (unsigned char key, int x, int y) 
{  
	EventManager::Instance().keyPressed(key);
}



int main (int argc, char * argv[])
{
	srand ( time(NULL) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Mouse");
	glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
	glutDisplayFunc(display);
	glutTimerFunc(30, TimerFunction, 1);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyPressed);
	Engine::Instance();

	glutMainLoop();

	return 0;
}
 