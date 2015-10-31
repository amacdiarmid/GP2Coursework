#include "Common.h"
#include "InputManager.h"


void InputManager::KeyBoardPress(SDL_Event event, PlayerController *player)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			player->MoveForward();
			break;
		case SDLK_DOWN:
			player->MoveBackwards();
			break;
		case SDLK_RIGHT:
			player->MoveRight();
			break;
		case SDLK_LEFT:
			player->MoveLeft();
			break;
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

