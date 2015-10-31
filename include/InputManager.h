#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "Common.h"
#include "PlayerController.h"

class InputManager
{
private:
public:
	void KeyBoardPress(SDL_Event event, PlayerController *player);
};


#endif