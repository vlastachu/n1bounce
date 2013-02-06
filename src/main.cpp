#include <iostream>
using namespace std;
#include "defs.h"
#include "Engine.h"
#include <time.h>
#include <vector>
#include "EventManager.h"

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
	glClearColor(1.0 ,1.0, 1.0, 0.0);
}

EventManager e_mgr;

void keyPressed (unsigned char key, int x, int y) 
{  
	e_mgr.keyPressed(key);
}



int main (int argc, char * argv[])
{
	srand ( time(NULL) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Mouse");
	glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
	glutDisplayFunc(display);
	glutTimerFunc(30, TimerFunction, 1);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyPressed);
	e_mgr.Add(Engine::Instance().getGame()->getBall());
	
	glutMainLoop();

	return 0;
}
 