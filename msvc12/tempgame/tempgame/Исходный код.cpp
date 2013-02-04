#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <map>
#include <string>
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
	
	float yborder;
	int impulse;
public:
	bool jmp;
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
		/*for(long int i=0;i<10000000;i++)
		{
			double f=i/67;
		}*/
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

class ModuleManager;
class Module
{
protected:
	ModuleManager* mgr;
public:
	void setManager(ModuleManager* Mgr)
	{
		mgr=Mgr;
	}
	virtual void Init(){};
	virtual void Run(){cout<<0;};
	virtual void Clear(){};
};

class ModuleManager
{
	map<string,Module*> allModules;
	map<string,Module*> activeModules;
	vector<string> dump;
	bool isDump;
public:
	ModuleManager()
	{
		isDump=false;
	}
	void Run()
	{
		//cout<<2;
		for(map<string,Module*>::iterator it=activeModules.begin();it!=activeModules.end();it++)
		{
			it->second->Run();//NULL->Run()
		}
		//cout<<6;
		if(isDump)
		{
			for(vector<string>::iterator it=dump.begin();it!=dump.end();it++)
			{
				activeModules.find(*it)->second->Clear();//NULL->Clear()
				activeModules.erase(*it);
			}
			dump.clear();
			isDump=false;
		}
	}
	void Register(string name,Module* module)
	{
		allModules.insert(pair<string,Module*>(name,module));
	}
	void Start(string name)
	{
		map<string,Module*>::iterator it=allModules.find(name);
		if(it!=allModules.end())
		{
			activeModules.insert(pair<string,Module*>(name,it->second));
			it->second->setManager(this);//NULL->Init()
			it->second->Init();//NULL->Init()
		}
	}
	void Stop(string name)
	{
		dump.push_back(name);
		isDump=true;
	}


};

class End:public Module
{
	virtual void Run()
	{
		cout<<"!";
	}
	virtual void Init()
	{
	}
};

class GameCore:public Module
{
	int i;
public:
	virtual void Run()
	{
		ball.move();
		ball.draw();
		i++;
		if(i==200)
		{
			mgr->Stop("game");
			mgr->Start("byebye");
		}
	}
	virtual void Init()
	{
		i=0;
		cout<<"init success";
		ball.init();
	}
};

class Test:public Module
{
public:
	virtual void Run()
	{
		cout<<0;
	}
	virtual void Init()
	{
		cout<<"helloworld";
	}
};


class Engine
{
	ModuleManager mm;
	GameCore game;
	Test test;
	End end;
public:
	void init()
	{
		mm.Register("game",&game);
		mm.Register("test",&test);
		mm.Register("byebye",&end);
		mm.Start("game");
		mm.Start("test");
		
	}

	void play()
	{
		mm.Run();
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
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0 ,1.0, 1.0, 0.0);
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(30,TimerFunction, 1);
	engine.play();
}

void keyboard(int key, int x, int y) 
{
	cout<<key;
	//ball.jump();
}
void keyPressed (unsigned char key, int x, int y) 
{  
	ball.jump();

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
	glutSpecialFunc(keyboard);
	engine.init();


	glutMainLoop();
	return 0;
}