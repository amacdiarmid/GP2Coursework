#include "PlayerController.h"

PlayerController::PlayerController()
{
	worldPoint = vec3(0, 0, 10);
	lookAtPoint = vec3(0, 0, 0);
	upPoint = vec3(0, 1, 0);
}

	void PlayerController::moveForward()
	{
		if (debug)
		{
			worldPoint.z += -1.0f;
			lookAtPoint.z += -1.0f;
		}
		else
		{

		}
		cout << "w key " << endl;
	}

	void PlayerController::moveBackward()
	{
		if (debug)
		{
			worldPoint.z += 1.0f;
			lookAtPoint.z += 1.0f;
		}
		else
		{

		}
		cout << "s key " << endl;
	}

	void PlayerController::strafeRight()
	{
		if (debug)
		{
			worldPoint.x += 1.0f;
			lookAtPoint.x += 1.0f;
		}
		else
		{

		}
		cout << "s key " << endl;
	}

	void PlayerController::strafeLeft()
	{
		if (debug)
		{
			worldPoint.x += -1.0f;
			lookAtPoint.x += -1.0f;
		}
		else
		{

		}
		cout << "s key " << endl;
	}

	void PlayerController::Update()
	{
		projMatrix = perspective(FOV, getRatio(), NEAR_CLIPPINGPLANE, FAR_CLIPPINGPLANE);
		viewMatrix = lookAt(worldPoint, lookAtPoint, upPoint);
		MVPMatrix = projMatrix*viewMatrix;
	}
