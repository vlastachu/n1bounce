
#include "defs.h"
#include <stdlib.h>
#include <Windows.h>
#include <vector> // WTFFFFF??????????????
#include <GL\glut.h>

#include <time.h>
#include "Engine.h"
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

void reshape(int w, int h)
{
}

void motion(int X,int Y)
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
	EventManager::Instance().keyPressed(Key);
}

void keyReleased(int Key,int,int)
{
	EventManager::Instance().keyReleased(Key);
}

void mouse(int button, int state, int x, int y){
	EventManager::Instance().mouse(button, state, x, y);
}

void mousePasive(int x, int y){
	EventManager::Instance().mousePasive(x, y);
}

int main (int argc, char * argv[])
{
	srand ( time(NULL) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Crysis");
	glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glutDisplayFunc(display);
	glutTimerFunc(30, TimerFunction, 1);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyReleased);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc (mousePasive);
	Engine::Instance();

	glutMainLoop();

	return 0;
}
 