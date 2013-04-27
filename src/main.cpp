#include <vector> // WTFFFFF??????????????

#include <GL\glut.h>
//#include <time.h>
#include "Engine.h"


void reshape(int Width,int Height)
{
	glViewport(0,0,Width,Height);
	//glOrtho (0, Width, Height, 0, -1, 1);
	Engine::Instance().reshape((float)Width,(float)Height);
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


void keyPressed(int Key,int,int) 
{  
	Engine::Instance().keyPressed(Key);
}

void keyReleased(int Key,int,int)
{
	Engine::Instance().keyReleased(Key);
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
	glutPassiveMotionFunc(motion);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	glutReshapeFunc(reshape);
	
	Engine::Instance();

	glutMainLoop();

	return 0;
}
 