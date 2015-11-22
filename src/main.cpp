#include "Window.h"
#include "GP2CourseWorkGame.h"

int main(int argc, char * arg[])
{
	bool run = true;

	createWindow("GP 2 Coursework: The Holo Room");

	GameApp *curGame = new GP2CourseWorkGame();

	while (run)
	{
		if (!curGame->gameLoop())
		{
			run = false;
		}
	}

	curGame->destroyGame();
	destroyWindow();

    return 0;
}
