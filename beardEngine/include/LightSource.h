#ifndef _LIGHTSOURCE_
#define _LIGHTSOURCE_

#include "Common.h"



class LightSource
{
	
private:
	GLenum lightID = GL_LIGHT0;
	vec4 ambient = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
public:
	LightSource();
	~LightSource();
	void Activate();
	void Deactivate();
};

#endif