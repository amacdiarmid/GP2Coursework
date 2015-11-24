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

//called everytime the camera moves 
void Fustrum::updateCamera()
{
	vec3 direction, nearClippingDistance, farClippingDistance, X, Y, Z;
	
	//compute the z axis. this points in the opposite direction from the looking direction
	Z = player->getWorldPoint() - player->getlookAtPoint;
	Z = normalize(Z);

	//x axis of the camera with the given UP vector and Z axis
	X = player->getUpPoint();
	X = normalize(X);

	//the real UP vector is the cross of Z and X
	Y = Z * X;

	//get the centers of the rear and far plane
	nearClippingCenter = player->getWorldPoint() - Z * NEAR_CLIPPINGPLANE;
	farClippingCenter = player->getWorldPoint() - Z * FAR_CLIPPINGPLANE;

	//set the 4 corners od the near plane
	topNearLeftPoint = nearClippingCenter + Y * player->getNearHeight() - X * player->getNearWidth();
	topNearRightPoint = nearClippingCenter + Y * player->getNearHeight() + X * player->getNearWidth();
	bottomNearLeftPoint = nearClippingCenter - Y * player->getNearHeight() - X * player->getNearWidth();
	bottomNearRightPoint = nearClippingCenter - Y * player->getNearHeight() + X * player->getNearWidth();

	//set the 4 corners od the far plane
	topFarLeftPoint = farClippingCenter + Y * player->getFarHeight() - X * player->getFarWidth();
	topFarRightPoint = farClippingCenter + Y * player->getFarHeight() + X * player->getFarWidth();
	bottomFarLeftPoint = farClippingCenter - Y * player->getFarHeight() - X * player->getFarWidth();
	bottomFarRightPoint = farClippingCenter - Y * player->getFarHeight() + X * player->getFarWidth();

	//get the planes and set the normals
	plane[TOP_PLANE].setPoints(topNearRightPoint, topNearLeftPoint, topFarLeftPoint);
	plane[BOTTOM_PLANE].setPoints(bottomNearLeftPoint, bottomNearRightPoint, bottomFarRightPoint);
	plane[LEFT_PLANE].setPoints(topNearLeftPoint, bottomNearLeftPoint, bottomFarLeftPoint);
	plane[RIGHT_PLANE].setPoints(topNearRightPoint, bottomNearRightPoint, bottomFarRightPoint);
	plane[NEAR_PLANE].setPoints(topNearLeftPoint, topNearRightPoint, bottomNearRightPoint);
	plane[FAR_PLANE].setPoints(topFarLeftPoint, topFarRightPoint, bottomFarRightPoint);
}

positionToFrustrum Fustrum::isInFrustrum(Box* TempBox)
{

}
