#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

class PlayerController
{
private:
	vec3 worldPoint;
	vec3 lookAtPoint;

	//matrices
	mat4 viewMatrix;
	mat4 projMatrix;
	mat4 worldMatrix;
	mat4 MVPMatrix;


public:
	PlayerController();
	//Camera LookAt
	void LookUp();
	void LookDown();
	void LookRight();
	void LookLeft();

	void Update();

	mat4 GetViewMatrix(){ return viewMatrix; }
	mat4 getMVPmatrix(){ return MVPMatrix; }
};



#endif