#include "ViewFrustumCulling.h"

Fustrum::Fustrum()
{
}

Fustrum::Fustrum(PlayerController* tempPlayer)
{
	player = tempPlayer;
}

Fustrum::~Fustrum()
{
}

void Fustrum::setUpCamera()
{
	nearD = player->getNearPlaneDis();
	farD = player->getFarPlaneDis();

	tang = tan(radians(player->getFOV()));
	height = player->getNearPlaneDis() * tang;
	width = height * player->getRatio();
}

//called everytime the camera moves 
void Fustrum::updateCamera()
{
	camPos = player->getWorldPoint();

	Z = player->getlookAtPoint() - player->getWorldPoint();
	Z = normalize(Z);

	X = cross(Z, player->getUpPoint());
	X = normalize(X);

	Y = cross(X, Z);
}

positionToFrustrum Fustrum::isInFrustrum(Box* TempBox, vec3 objectPos)
{
	int out = 0;
	int in = 0;

	//not the mvp matrix but the gameobject position and add it to the box positions
	//test center point
	vec3 point = TempBox->getCenter() - objectPos;
	return pointInFrustrum(point);


	//for (int i = 0; i < 8; i++)
	//{
	//	//set up te correct point with the modelMatrix
	//	vec4 pointBefore = (vec4(TempBox->getPoints(i).x, TempBox->getPoints(i).y, TempBox->getPoints(i).z, 1) * modelMatrix);
	//	vec3 point = vec3(pointBefore.x, pointBefore.y, pointBefore.z);
	//	
	//	if (pointInFrustrum(point) == OUTSIDE_FRUSTRUM)
	//	{
	//		out++;
	//	}
	//	else
	//	{
	//		in++;
	//	}
	//}
	//if (out == 8)
	//{
	//	return OUTSIDE_FRUSTRUM;
	//}
	//else if (in == 8)
	//{
	//	return INSIDE_FRUSTRUM;
	//}
	//else
	//{
	//	return INTERSECT_FRUSTRUM;
	//}
}

positionToFrustrum Fustrum::pointInFrustrum(vec3 point)
{
	float pcz, pcx, pcy, aux;

	//get vectro from cam position
	vec3 v = point + camPos;

	//check if the z lies between the frustrum
	pcz = dot(v, -Z);
	if (pcz > farD || pcz < nearD)
	{
		return OUTSIDE_FRUSTRUM;
	}

	//check if the y lies between the frustrum
	pcy = dot(v, Y);
	aux = pcz * tang;
	if (pcy > aux || pcy < -aux)
	{
		return OUTSIDE_FRUSTRUM;
	}

	//check if the x lies between the frustrum
	pcx = dot(v, X);
	aux = aux * player->getRatio();
	if (pcx > aux || pcx < -aux)
	{
		return OUTSIDE_FRUSTRUM;
	}

	return INSIDE_FRUSTRUM;

}
