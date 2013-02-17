#include <list>
#include <GL\glut.h>
#include "Map.h"
#include "Engine.h"
#include "defs.h"

Map::Map(GameCore* Parent)
{
	parent=Parent;
}

void Map::draw()
{
	
	for(std::list<Element>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if((*it).id==1)
		{
			
			glColor3f(0.0,0.0,0.0);
		
		}
		else if((*it).id==2)
		{
			glColor3f(1.0,0.0,0.0);
		}
			
		glBegin(GL_LINE_LOOP);
			glVertex2f(parent->toX((*it).x) , parent->toY((*it).y));
			glVertex2f(parent->toX((*it).x) + parent->toL((*it).w) , parent->toY((*it).y));
			glVertex2f(parent->toX((*it).x) + parent->toL((*it).w) , parent->toY((*it).y) + parent->toL((*it).h));
			glVertex2f(parent->toX((*it).x) , parent->toY((*it).y) + parent->toL((*it).h));
		glEnd();
	
	}
}

void Map::init()
{
	elements.clear();
	dist = 20;
	elements.push_back(Element(0,HEIGHT-60,WIDTH,30,1));
	randY = 30;
	randW = 100 + rand()%150;	
}

void Map::move()
{
	if(dist == PLATFORM_DISTANCE)  // add new platform if distance from the last is /15/
	{
		deltaY = (60 + rand()%100);
		if(randY + deltaY > 500) directionY = -1;
		else if(randY - deltaY < 40) directionY = 1;
		else directionY = rand()%3 - 1;
		randY = randY + directionY * deltaY;
		randW = 200 + rand()%50;
		elements.push_back(Element(WIDTH,HEIGHT-randY,randW,30,1));
		dist=0;
		if(!(rand() % TRAP_CHANSE)){  // add trap on platform
			elements.push_back(Element(WIDTH + rand()%(randW - 30),HEIGHT-15-randY,30,15,2));
		}
	}
	dist++;

	if(!elements.empty())  // erase the first platform, which out of the screen
	{
		if((elements.front().x + elements.front().w) < 0)
		{
			elements.erase(elements.begin());// also delete here null pointers from platforms and traps

			//and delete objects in pointers

		}
	}


	parent->getNinja()->setBorder(2*HEIGHT);
	for(std::list<Element>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it).x-=parent->speed;

		if((*it).x < parent->getNinja()->x && (*it).x+(*it).w > parent->getNinja()->x)
		{
			if((*it).id==1)
			{
			//parent->getNinja()->mapCollise((*it).y,(*it).h,(*it).id);
				parent->getNinja()->setBorder((*it).y);
			}
			/*else if((*it).id==2)
			{
				if((*it).y <= parent->getNinja()->y && (*it).y+(*it).h+3 >= parent->getNinja()->y)
				{
					parent->getNinja()->setState(4);
				}
			}*/

		}
	}
	

}