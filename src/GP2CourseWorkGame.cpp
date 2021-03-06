#include "GP2CourseWorkGame.h"
#include "Scene.h"

GP2CourseWorkGame::GP2CourseWorkGame()
{
	//create the main scene
	currentScene = new HoloRoomScene("holoRoom");
	//main scene to the current scene (this could be usefull for multiple scenes (maybe))
	keyboardListeners.push_back(currentScene);

	currentScene->createScene();
}

GP2CourseWorkGame::~GP2CourseWorkGame()
{

}

void GP2CourseWorkGame::destroyGame()
{
	currentScene->destroyScene();
}

bool GP2CourseWorkGame::gameLoop()
{
	//value to hold the event generated by SDL
	SDL_Event event;
	//while we still have events in the queue
	while (SDL_PollEvent(&event))
	{
		//get event type
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			//set our bool which controls the loop to false
			return false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			for each (auto var in keyboardListeners)
			{
				var->onKeyDown(event.key.keysym.sym);
			}
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			for each (auto var in keyboardListeners)
			{
				var->mouseMove(event.motion);
			}
		}
	}

	currentScene->SceneLoop();

	return true;
}