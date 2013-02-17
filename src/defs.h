#pragma once
//#include <GL\glut.h>
//#include <GL\glu.h>
#define PI 3.14159
#define WIDTH 1000
#define HEIGHT 600
#define BALLX 100
#define MAP_SPEED 10

#define XSCALE_AXIS 200
#define YSCALE_AXIS 600


//#define DEAD_LINE HEIGHT-30  now HEIGHT is deadline
#define TRAP_CHANSE 4
#define PLATFORM_DISTANCE 100
enum ClassType{fixedMapShape, platform, trap};
void reshape(int w, int h);
void motion(int X,int Y);
void mouse(int button, int state, int x, int y);
void display();
void TimerFunction(int value);
void keyPressed (unsigned char key, int x, int y);
