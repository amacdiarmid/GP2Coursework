#ifndef _VIEWFUSTRUMCULLING_H
#define _VIEWFUSTRUMCULLING_H

#include "Common.h"
#include "PlayerController.h"
#include "Plane.h"
#include "Box.h"

enum positionToFrustrum 
{
	OUTSIDE_FRUSTRUM,
	INTERSECT_FRUSTRUM,
	INSIDE_FRUSTRUM,
};

enum fustrumPlane
{
	TOP_PLANE = 0,
	BOTTOM_PLANE = 1,
	LEFT_PLANE = 2,
	RIGHT_PLANE = 3,
	FAR_PLANE = 4,
	NEAR_PLANE = 5,
};

class Fustrum
{
public:
	Fustrum();
	Fustrum(PlayerController* tempPlayer);
	~Fustrum();
	void updateCamera();
	positionToFrustrum isInFrustrum(Box* tempBox);
private:
	PlayerController* player;
	Plane plane[6];
	vec3 farClippingCenter, nearClippingCenter;
	vec3 topFarLeftPoint, topFarRightPoint, bottomFarLeftPoint, bottomFarRightPoint;
	vec3 topNearLeftPoint, topNearRightPoint, bottomNearLeftPoint, bottomNearRightPoint;
};

#endif