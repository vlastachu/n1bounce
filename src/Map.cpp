#include <list>
#include "Map.h"
#include "Engine.h"
#include "Platform.h"
#include "Trap.h"
#include "defs.h"

Map::Map()
{}

void Map::draw()
{
	for(std::list<FixedMapShape*>::iterator it = shapes.begin(); it != shapes.end(); it++)
	{
		(*it)->draw();
	}
}

void Map::init()
{
	speed = MAP_SPEED;
	dist = 20;
	platforms.push_back(new Platform(60,WIDTH+40,0));
	shapes.push_back(platforms.back());
	randY = 30;
	randW = 100 + rand()%150;	
}

void Map::move()
{
	if(dist == PLATFORM_DISTANCE)  // add new platform if distance from the last is /15/
	{
		deltaY = 60 + rand()%100;
		if(randY + deltaY > 500) directionY = -1;
		else if(randY - deltaY < 40) directionY = 1;
		else directionY = rand()%3 - 1;
		randY = randY + directionY * deltaY;
		randW = 200 + rand()%50;
		platforms.push_back(new Platform(randY, randW));
		shapes.push_back(platforms.back());
		dist=0;
		if(!(rand() % TRAP_CHANSE)){  // add trap on platform
			traps.push_back(new Trap(randY,WIDTH + rand()%(randW - 30))); // 30 is width of trap
			shapes.push_back(traps.back());
		}
	}
	dist++;

	if(!shapes.empty())  // erase the first platform, which out of the screen
	{
		if((shapes.front()->getx() + shapes.front()->getw()) < 0)
		{
			delete shapes.front();
			shapes.erase(shapes.begin());// also delete here null pointers from platforms and traps
			//and delete objects in pointers

		}
	}

	for(std::list<FixedMapShape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		(*it)->move(speed);
	}
	

}

std::list<Platform*> Map::getPlatforms()
{
	return platforms;
}

std::list<Trap*> Map::getTraps()
{
	return traps;
}

void Map::clear(){
	for(std::list<FixedMapShape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		delete *it;//hahaha
	}
	shapes.clear();
	platforms.clear();
	traps.clear();
}