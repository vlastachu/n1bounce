#include <vector>
#include "Map.h"
#include "Engine.h"
#include "Platform.h"
#include "Trap.h"
#include "defs.h"

Map::Map()
{}

void Map::draw()
{
	for(int i = 0; i < shapes.size(); i++)
	{
		shapes.at(i)->draw();
	}
}

void Map::init()
{
	speed = MAP_SPEED;
	dist = 0;
	platforms.push_back(new Platform(60,WIDTH,0));
	shapes.push_back(platforms.back());
	randY = 70 + rand()%120;
	randW = 100 + rand()%150;	
}

void Map::move()
{
	if(dist == PLATFORM_DISTANCE)  // add new platform if distance from the last is /15/
	{
		randY = randY - 60 + rand()%120;
		if(randY < (HEIGHT - DEAD_LINE + 10)) randY = HEIGHT - DEAD_LINE + 15;
		if(randY > 400) randY = 350;
		randW = 100 + rand()%150;
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
			shapes.erase(shapes.begin());// also delete here null pointers from platforms and traps
			//and delete objects in pointers
		}
	}

	for(int i=0; i < shapes.size(); i++)
	{
		shapes.at(i)->move(speed); 
	}
}

std::vector<Platform*> Map::getPlatforms()
{
	return platforms;
}

std::vector<Trap*> Map::getTraps()
{
	return traps;
}

void Map::clear(){
	shapes.clear();
	platforms.clear();
	traps.clear();
}