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
	Z = player->getWorldPoint() - player->getlookAtPoint();
	Z = normalize(Z);

	//x axis of the camera with the given UP vector and Z axis
	X = player->getUpPoint();
	X = normalize(X);

	//the real UP vector is the cross of Z and X
	Y = Z * X;

	//points being calculated wrong
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
	planes[TOP_PLANE].setPoints(topNearRightPoint, topNearLeftPoint, topFarLeftPoint);
	planes[BOTTOM_PLANE].setPoints(bottomNearLeftPoint, bottomNearRightPoint, bottomFarRightPoint);
	planes[LEFT_PLANE].setPoints(topNearLeftPoint, bottomNearLeftPoint, bottomFarLeftPoint);
	planes[RIGHT_PLANE].setPoints(topNearRightPoint, bottomNearRightPoint, bottomFarRightPoint);
	planes[NEAR_PLANE].setPoints(topNearLeftPoint, topNearRightPoint, bottomNearRightPoint);
	planes[FAR_PLANE].setPoints(topFarLeftPoint, topFarRightPoint, bottomFarRightPoint);
}

positionToFrustrum Fustrum::isInFrustrum(Box* TempBox, mat4 modelMatrix)
{
	int in = 0, out = 0;

	for (int i = 0; i < 6; i++)
	{
		in = 0;
		out = 0;

		for (int j = 0; j < 8 && (in == 0 || out == 0); j++)
		{
			vec4 k = vec4(TempBox->getPoints(j).x, TempBox->getPoints(j).y, TempBox->getPoints(j).z, 1) * modelMatrix;
			vec3 B = vec3(k.x, k.y, k.z);
			vec3 AB = B - planes[i].getNormal();

			if (dot(AB, planes[i].getNormal()) < 0)
			{
				out++;
			}
			else
			{
				in++;
			}
		}
		if (!in)
		{
			return OUTSIDE_FRUSTRUM;
		}
		else if (out)
		{
			return INTERSECT_FRUSTRUM;
		}
	}
	return INSIDE_FRUSTRUM;
}
