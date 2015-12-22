#ifndef _OUTLINEMATERIAL_H
#define _OUTLINEMATERIAL_H

#include "Shader.h"

class OutlineMaterial : public Shader
{
public:

	OutlineMaterial();
	~OutlineMaterial();

	void bind();
	void unbind();

};

#endif 