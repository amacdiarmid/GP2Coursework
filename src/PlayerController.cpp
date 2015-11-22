#include "Common.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
	lookAtPoint = vec3(0, 0, 0);
	worldPoint = vec3(0, 0, 10);
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
		projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
		viewMatrix = lookAt(worldPoint, lookAtPoint, vec3(0.0f, 1.0f, 0.0f));
		MVPMatrix = projMatrix*viewMatrix;
	}
