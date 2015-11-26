#include "Components\InputComponent.h"

InputComponent::InputComponent(){}

InputComponent::InputComponent(GameObject *tempOwner)
{
	type = "input component";
	owner = tempOwner;
	keyboardListeners.push_back(this);
}
void InputComponent::onKeyDown(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_w:
			owner->getInput()->MoveForward();
			break;
		case SDLK_a:
			owner->getInput()->MoveLeft();
			break;
		case SDLK_s:
			owner->getInput()->MoveBackwards();
			break;
		case SDLK_d:
			owner->getInput()->MoveRight();
			break;
		}
	}

void InputComponent::onkeyUp(SDL_Keycode key)
{}

