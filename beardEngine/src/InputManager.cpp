#include "Common.h"
#include "InputManager.h"


void InputManager::KeyBoardPress(PlayerController *player)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			player->LookUp();
			break;
		case SDLK_s:
			player->LookDown();
			break;
		case SDLK_a:
			player->LookLeft();
			break;
		case SDLK_d:
			player->LookRight();
			break;
		default:
			break;
		}
	}	
}

