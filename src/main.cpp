#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;

#define PI 3.14159
#define WIDTH 1000
#define HEIGHT 600

#define BALLX 100

float radian(float a) {
	return a / 180 * PI;
}

void circle(int X, int Y, int R)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<360;i+=5)
	{
		float a = radian(i);
		glVertex2f(cos(a)*R+X,sin(a)*R+Y);
	}
	glEnd();
}

class Ball
{
	float x,y,r;
	float dy;
	bool jmp;
	float yborder;
	int impulse;
public:
	float getx()
	{
		return x;
	}
	void setborder(float Y)
	{
		yborder=Y-r;
	}
	void init()
	{
		x=BALLX;
		y=500;
		r=20;
		dy=0;
		jmp=false;
		impulse=20;
		setborder(500);
	}
	void jump()
	{
		if(!jmp)
		{
			dy=impulse;
			jmp=true;
		}
	}
	void move()
	{
		if(jmp)
		{
			y-=dy;
			dy--;
			if(y>yborder)
			{
				y=yborder;
				dy=0;
				jmp=false;
			}	
		}
	}
	void draw()
	{
		glColor3f(1.0,0.0,0.0);
		circle(x,y,r);
	}
}ball;

class Platform
{
	float x,y,w,h;
public:
	void draw()
	{
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x,y);
			glVertex2f(x+w,y);
			glVertex2f(x+w,y+h);
			glVertex2f(x,y+h);
		glEnd();
	}
	void move(float dx)
	{
		x-=dx;
	}
	float getx()
	{
		return x;
	}
	float gety()
	{
		return y;
	}
	float getw()
	{
		return w;
	}
	Platform()
	{
		x=WIDTH;
		y=500;
		w=100;
		h=30;
	}
};

class Platforms
{
	vector<Platform> vect;
	float speed;
	int dist;
public:
	void draw()
	{
		for(int i=0;i<vect.size();i++)
		{
			vect.at(i).draw();
		}
	}
	void init()
	{
		speed=10;
		dist=0;
	}
	void move()
	{
		if(dist==20)
		{
			vect.push_back(Platform());
			dist=0;
		}
		dist++;

		if(!vect.empty())
		{
			if(vect.front().getx()+vect.front().getw()<0)
			{
				vect.erase(vect.begin());
			}
		}

		ball.setborder(HEIGHT);
		for(int i=0;i<vect.size();i++)
		{
			vect.at(i).move(speed);
			if(vect.at(i).getx()<ball.getx() && vect.at(i).getx()+vect.at(i).getw()>ball.getx())
			{
				ball.setborder(vect.at(i).gety());
			}
		}

	}


}platforms;

class Engine
{
public:
	void init()
	{
		platforms.init();
		ball.init();
	}
	void play()
	{
		platforms.move();
		platforms.draw();
		ball.move();
		ball.draw();
	}
}engine;

void reshape(int w, int h)
{
}

void motion(int X,int Y)
{
}

void mouse(int button, int state, int x, int y)
{
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 0.0);
	engine.play();
    glutSwapBuffers();
}
void TimerFunction(int value)
{
	
    glutPostRedisplay();
    glutTimerFunc(30,TimerFunction, 1);
}
void keyPressed (unsigned char key, int x, int y) 
{  
	if(key==68)
	{
	ball.jump();
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

	engine.init();

	glutMainLoop();
	return 0;
}
 