#ifndef _PLANE_H
#define _PLANE_H

#include "Common.h"

struct Plane
{
	vec3 point1, point2, point3;

	void setPoints(vec3 P1, vec3 P2, vec3 P3)
	{
		point1 = P1;
		point2 = P2;
		point3 = P3;
	}

	vec3 getNormal()
	{
		vec3 vector1 = point1 - point2;
		vec3 vector2 = point3 - point2;
		return cross(vector1, vector2);
	}

	
};

#endif