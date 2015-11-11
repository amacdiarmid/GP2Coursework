#ifndef _BASECOMPONENT_H
#define _BASECOMPONENT_H

#include "Common.h"

enum Components
{
	BASE_COMPONENT,
	RENDER_COMPONENT,
};

class GameObject;

class IComponent
{
public:
	virtual ~IComponent(){};

	virtual void setOwner(GameObject * tempOwner) = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual string getType() = 0;

private:

};

class Component:public IComponent
{
public:

	Component(){ type = "Base component"; };
	virtual ~Component(){};

	void setOwner(GameObject *tempOwner){ owner = tempOwner; };
	GameObject *getOwner(){ return owner; };
	virtual void init(){};
	virtual void update(){};
	virtual void render(){};
	virtual string getType(){ return type; };

protected:
	string type;
	GameObject *owner;

};

#endif