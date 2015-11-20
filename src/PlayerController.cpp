#include "Common.h"
#include "PlayerController.h"

PlayerController::PlayerController()
{
	PlayerController::movementVec = vec3(0, 0, 0);
	PlayerController::lookAtPoint = vec3(0, 0, 0);
	PlayerController::worldPoint = vec3(0, 0, 10);
}

	void PlayerController::MoveForward()
	{
		PlayerController::movementVec.y += 0.5;
		cout << "up arrow " << endl;
	}

	void PlayerController::MoveBackwards()
	{
		movementVec.y += -0.5f;
		cout << "down arrow " << endl;
	}

	void PlayerController::MoveRight()
	{
		movementVec.x += 0.5f;
		cout << "right arrow " << endl;
	}

	void PlayerController::MoveLeft()
	{
		movementVec.x += -0.5f;
		cout << "left arrow " << endl;
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
		worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
		MVPMatrix = projMatrix*viewMatrix*worldMatrix;
	}
