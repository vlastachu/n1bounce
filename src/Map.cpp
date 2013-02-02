#include <vector>
#include "Map.h"
#include "Platform.h"
#include "defs.h"
#include "Ball.h"

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
}

void Map::move(Ball ball)
{
	if(dist==20)
	{
		shapes.push_back(new Platform());
		dist=0;
	}
	dist++;

	if(!shapes.empty())
	{
		if((shapes.front()->getx() + shapes.front()->getw()) < 0)
		{
			shapes.erase(shapes.begin());
		}
	}

	ball.setborder(HEIGHT);
	for(int i=0; i < shapes.size(); i++)
	{
		shapes.at(i)->move(speed);
		if(shapes.at(i)->getx() < ball.getx() && shapes.at(i)->getx() + shapes.at(i)->getw() > ball.getx())
		{
			ball.setborder(shapes.at(i)->gety());
		}
	}
}