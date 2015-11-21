#include "Game.h"

Scene *currentScene;

void createGame()
{
	//create the main scene
	Scene *mainScene = new Scene("holoRoom");
	//main scene to the current scene (this could be usefull for multiple scenes (maybe))
	currentScene = mainScene;

	keyboard = mainScene;

	currentScene->createScene();
}

void destroyGame()
{
	currentScene->destroyScene();
}

void gameLoop()
{
	currentScene->SceneLoop();
}