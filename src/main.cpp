#include <iostream>
using namespace std;
#include "defs.h"
#include "Engine.h"


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
	
    glutPostRedisplay();
    glutTimerFunc(30,TimerFunction, 1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 0.0);
	Engine::Instance().play();
    glutSwapBuffers();
}

void keyPressed (unsigned char key, int x, int y) 
{  
	if(key==GLUT_KEY_UP)
	{
		Engine::Instance().getBall()->jump();
	std::cout << "11";
	}
}



int main (int argc, char * argv[])
{
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
	Engine::Instance();
	
	glutMainLoop();

	return 0;
}
 