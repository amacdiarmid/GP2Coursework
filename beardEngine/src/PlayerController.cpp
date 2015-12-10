#include "PlayerController.h"

PlayerController::PlayerController()
{
}

void PlayerController::moveForward()
{
	if (debug)
	{
		position += direction * speed;
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
		position -= direction * speed;
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
		position += right * speed;
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
		position -= right * speed;
	}
	else
	{

	}
	cout << "s key " << endl;
}

void PlayerController::mouseMovment(vec2 mousePos)
{
	horAngle += mouseSpeed * float(SCREEN_WIDTH / 2 - mousePos.x);
	if (degrees(horAngle) > 360.0f) { horAngle = radians(0.0f); }
	else if (degrees(horAngle) < 0.0f){ horAngle = radians(360.0f); }
	VertAngle += mouseSpeed * float(SCREEN_HEIGHT / 2 - mousePos.y);
	if (degrees(VertAngle) >= 90.0f) { VertAngle = radians(89.9f); }
	else if (degrees(VertAngle) <= -90.0f) { VertAngle = radians (- 89.9f);}
	cout << "hor angle " << degrees(horAngle) << " vert angle " << degrees(VertAngle) << endl;

	direction = vec3(cos(VertAngle)*sin(horAngle), sin(VertAngle), cos(VertAngle)*cos(horAngle));

	right = vec3(sin(horAngle - 3.14 / 2), 0, cos(horAngle - 3.14 / 2));
	upPoint = vec3(0, 1, 0);
	//upPoint = cross(direction, right);
}

void PlayerController::Update()
{
	projMatrix = perspective(FOV, getRatio(), NEAR_CLIPPINGPLANE, FAR_CLIPPINGPLANE);
	viewMatrix = lookAt(position, position + direction, upPoint);
	MVPMatrix = projMatrix*viewMatrix;
}
