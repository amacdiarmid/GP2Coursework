#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

class PlayerController
{
private:
	//vectors
	vec3 worldPoint;
	vec3 lookAtPoint;
	vec3 upPoint;

	//matrices
	mat4 viewMatrix;
	mat4 projMatrix;
	mat4 MVPMatrix;

public:
	PlayerController();
	//Camera LookAt
	void LookUp();
	void LookDown();
	void LookRight();
	void LookLeft();

	void Update();

	vec3 getWorldPoint(){ return worldPoint; };
	vec3 getlookAtPoint(){ return lookAtPoint; };
	vec3 getUpPoint(){ return upPoint; };
	vec3 getDirection(){ return lookAtPoint - worldPoint; };
	float getNearHeight(){ return 2 * tan(FOV / 2) * NEAR_CLIPPINGPLANE; };
	float getNearWidth(){ return getNearHeight() * (SCREEN_WIDTH / SCREEN_HEIGHT); };
	float getFarHeight(){ return 2 * tan(FOV / 2) * FAR_CLIPPINGPLANE; };
	float getFarWidth(){ return getNearHeight() * (SCREEN_WIDTH / SCREEN_HEIGHT); };

	mat4 GetViewMatrix(){ return viewMatrix; };
	mat4 getProjMatrix(){ return projMatrix; };
	mat4 getMVPmatrix(){ return MVPMatrix; };
};



#endif