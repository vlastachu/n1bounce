#include "Engine.h"
#include "Map.h"
#include "Ball.h"
#include "defs.h"

Engine::Engine()
{
	
	map.init();
	ball.init();

}

Engine& Engine::Instance()
{
        static Engine theSingleInstance;
        return theSingleInstance;
}

void Engine::play()
{
	map.move(ball);
	map.draw();
	ball.move();
	ball.draw();
}