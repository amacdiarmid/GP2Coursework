#ifndef _LIGHTSOURCE_
#define _LIGHTSOURCE_

#include "Common.h"
#include "Texture.h"


struct Light 
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	Texture *diffuseTexture;
	vec3 specular;
	float shininess;
};

#endif