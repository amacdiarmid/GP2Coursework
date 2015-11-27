#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include "Common.h"

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
	~PlayerController();
	
	//Camera LookAt
	void moveForward();
	void moveBackward();
	void strafeRight();
	void strafeLeft();

	void Update();

	vec3 getWorldPoint(){ return worldPoint; };
	vec3 getlookAtPoint(){ return lookAtPoint; };
	vec3 getUpPoint(){ return upPoint; };
	vec3 getDirection(){ return lookAtPoint - worldPoint; };

	float getRatio(){ return SCREEN_WIDTH / SCREEN_HEIGHT; };
	float getFOV(){ return FOV; };
	float getNearPlaneDis(){ return NEAR_CLIPPINGPLANE; };
	float getFarPlaneDis(){ return FAR_CLIPPINGPLANE; };
	float getNearHeight(){ return 2 * tan(FOV / 2) * NEAR_CLIPPINGPLANE; };
	float getNearWidth(){ return getNearHeight() * getRatio(); };
	float getFarHeight(){ return 2 * tan(FOV / 2) * FAR_CLIPPINGPLANE; };
	float getFarWidth(){ return getFarHeight() * getRatio(); };

	mat4 GetViewMatrix(){ return viewMatrix; };
	mat4 getProjMatrix(){ return projMatrix; };
	mat4 getMVPmatrix(){ return MVPMatrix; };

	void setWorldPoint(vec3 tempPos){ worldPoint = tempPos; lookAtPoint = tempPos + vec3(0, 0, -10); };
};



#endif