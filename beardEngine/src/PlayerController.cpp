#include "Common.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
	worldPoint = vec3(0, 0, 10);
	lookAtPoint = vec3(0, 0, 0);
	upPoint = vec3(0, 1, 0);
}

	void PlayerController::LookUp()
	{
		worldPoint.z += -1.0f;
		lookAtPoint.z += -1.0f;
		cout << "w key " << endl;
	}

	void PlayerController::LookDown()
	{
		worldPoint.z += 1.0f;
		lookAtPoint.z += 1.0f;
		cout << "s key " << endl;
	}

	void PlayerController::LookRight()
	{
		worldPoint.x += 1.0f;
		lookAtPoint.x += 1.0f;
		cout << "s key " << endl;
	}

	void PlayerController::LookLeft()
	{
		worldPoint.x += -1.0f;
		lookAtPoint.x += -1.0f;
		cout << "s key " << endl;
	}

	void PlayerController::Update()
	{
		projMatrix = perspective(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIPPINGPLANE, FAR_CLIPPINGPLANE);
		viewMatrix = lookAt(worldPoint, lookAtPoint, upPoint);
		MVPMatrix = projMatrix*viewMatrix;
	}
