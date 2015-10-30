#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

class PlayerController
{
private:
	vec3 movementVec;
	vec3 worldPoint;
	vec3 lookAtPoint;
	mat4 viewMatrix;

public:
	PlayerController();
	//Movement
	void MoveForward();
	void MoveBackwards();
	void MoveRight();
	void MoveLeft();
	//Camera LookAt
	void LookUp();
	void LookDown();
	void LookRight();
	void LookLeft();

	void Update();

	mat4 GetViewMatrix(){ return viewMatrix; }
	vec3 GetMovementVec(){ return movementVec; }
};



#endif