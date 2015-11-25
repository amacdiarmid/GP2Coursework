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
	X = player->getUpPoint() * Z;
	//X = normalize(X);

	//normalizing
	float len = ((float)sqrt(X.x*X.x + X.y*X.y + X.z*X.z));
	if (len) {
		X.x /= len;;
		X.y /= len;
		X.z /= len;
	}


	//the real UP vector is the cross of Z and X
	Y = Z * X;

	//points being calculated wrong
	//get the centers of the rear and far plane
	nearClippingCenter = player->getWorldPoint() - Z * NEAR_CLIPPINGPLANE;
	farClippingCenter = player->getWorldPoint() - Z * FAR_CLIPPINGPLANE;

	//set the 4 corners od the near plane
	nearTopLeftPoint = nearClippingCenter + Y * player->getNearHeight() - X * player->getNearWidth();
	nearTopRightPoint = nearClippingCenter + Y * player->getNearHeight() + X * player->getNearWidth();
	nearBottomLeftPoint = nearClippingCenter - Y * player->getNearHeight() - X * player->getNearWidth();
	nearBottomRightPoint = nearClippingCenter - Y * player->getNearHeight() + X * player->getNearWidth();

	//set the 4 corners od the far plane
	farTopLeftPoint = farClippingCenter + Y * player->getFarHeight() - X * player->getFarWidth();
	farTopRightPoint = farClippingCenter + Y * player->getFarHeight() + X * player->getFarWidth();
	farBottomLeftPoint = farClippingCenter - Y * player->getFarHeight() - X * player->getFarWidth();
	farBottomRightPoint = farClippingCenter - Y * player->getFarHeight() + X * player->getFarWidth();

	//get the planes and set the normals
	planes[TOP_PLANE].setPlane(nearTopRightPoint, nearTopLeftPoint, farTopLeftPoint);
	planes[BOTTOM_PLANE].setPlane(nearBottomLeftPoint, nearBottomRightPoint, farBottomRightPoint);
	planes[LEFT_PLANE].setPlane(nearTopLeftPoint, nearBottomLeftPoint, farBottomLeftPoint);
	planes[RIGHT_PLANE].setPlane(nearBottomRightPoint, nearTopRightPoint, farBottomRightPoint);
	planes[NEAR_PLANE].setPlane(nearTopRightPoint, nearTopLeftPoint, nearBottomRightPoint);
	planes[FAR_PLANE].setPlane(farTopRightPoint, farTopLeftPoint, farBottomLeftPoint);
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
			vec3 AB = B - planes[i].normal;

			if (planes[i].distanceFromVec(TempBox->boxPoints[j]) < 0)
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
