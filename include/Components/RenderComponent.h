#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H

#pragma once

#include "BaseComponent.h"
#include "Object.h"

class Renderer:public Component
{
public:
	Renderer();
	~Renderer();

	void init();
	void update();
	void render();
	string getType();
private:

};

#endif