#include "Engine.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"

void Engine::reshape(int w, int h)
{
}

void Engine::motion(int X,int Y)
{
}

void Engine::mouse(int button, int state, int x, int y)
{
}


void Engine::TimerFunction(int value)
{
	
    glutPostRedisplay();
    glutTimerFunc(30,&(this->TimerFunction), 1);
}

void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 0.0);
	this->play();
    glutSwapBuffers();
}

void Engine::keyPressed (unsigned char key, int x, int y) 
{  
	if(key==68)
	{
	ball.jump();
	}
}

Engine::Engine(int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Mouse");
	glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
	glutDisplayFunc(&(display));
	glutTimerFunc(30, &(this->TimerFunction), 1);
	glutMouseFunc(&(this->mouse));
	glutPassiveMotionFunc(&(this->motion));
	glutKeyboardFunc(&(this->keyPressed));


	map.init();
	ball.init();

	glutMainLoop();
}
void Engine::play()
{
	map.move(ball);
	map.draw();
	ball.move();
	ball.draw();
}