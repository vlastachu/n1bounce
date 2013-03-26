#include <vector> // WTFFFFF??????????????
#include <GL\glut.h>

#include <time.h>
#include "Engine.h"

#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

void reshape(int Width,int Height)
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
	Engine::Instance().keyPressed(Key);
}

void keyReleased(int Key,int,int)
{
	Engine::Instance().keyReleased(Key);
}
void mouse(int button, int state, int x, int y){
	Engine::Instance().mouse(button, state, x, y);
}

void mousePasive(int x, int y){
	Engine::Instance().mousePasive(x, y);
}


int main (int argc, char * argv[])
{
	srand ( time(NULL) );
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Crysis");
	glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);

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
 