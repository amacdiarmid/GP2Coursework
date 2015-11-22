#ifndef _GAME_H
#define _GAME_H

#include "Scene.h"
#include "Window.h"

class GameApp
{
public:
	virtual ~GameApp(){};
	virtual void destroyGame() = 0;
	virtual bool gameLoop() = 0;

protected:
	Scene *currentScene;
};

#endif