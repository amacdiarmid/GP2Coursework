#include "GameObject.h"
#include "Components\InputComponent.h"

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	name = tempName;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent, Object *tempModel, GLuint *tempTexture, Shader *tempShader, PlayerController *tempInput)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = tempModel;
	texture = tempTexture;
	shader = tempShader;
	input = tempInput;
	childrenList.clear();
	componentsList.clear();
	active = true;

}

GameObject::~GameObject()
{
}

void GameObject::addComponent(Components type)
{
	switch (type)
	{
	case RENDER_COMPONENT:
		cout << "adding render Comp to " << name << endl;
		componentsList.insert(pair<Components, Component*>(type, new Renderer(this)));
		break;
	case INPUT_COMPONENT:
		cout << "adding render Comp to " << name << endl;
		componentsList.insert(pair<Components, Component*>(type, new InputComponent(this)));
		break;
	default:
		cout << "error_1, gameObject.cpp - no component" << endl;
		break;
	}
}

void GameObject::update()
{
	if (world == false)
	{
		worldPosition = localPosition + parent->getPosition();
	}
	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->update();
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->update();
		}
	}
}

void GameObject::render()
{
	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->render();
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->render();
		}
	}
}

vec3 GameObject::getPosition()
{
	return worldPosition;
}

void GameObject::addChild(GameObject *tempChild)
{
	childrenList.insert(pair<string, GameObject*>(tempChild->getName(), tempChild));
}

Object *GameObject::getModel()
{
	return model;
}

Shader *GameObject::getShader()
{
	return shader;
}

GLuint *GameObject::getTexture()
{
	return texture;
}

GameObject *GameObject::getChild(string tempName)
{
	return childrenList[tempName];
}

void GameObject::setPosition(vec3 tempPos)
{
	localPosition = tempPos;
}

void GameObject::changePosition(vec3 tempPos)
{
	localPosition += tempPos;
}

string GameObject::getName()
{
	return name;
}

PlayerController *GameObject::getInput()
{
	return input;
}

void GameObject::getChildern()
{
	cout << "\t";

	for (auto i = childrenList.begin(); i != childrenList.end(); i++)
	{
		cout << "object: " << i->second->getName() << " components ";
		i->second->getComponents();
		i->second->getChildern();
	}
}

void GameObject::getComponents()
{
	cout << " " << componentsList.size() << " ";
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		cout << i->second->getType() << " ";
	}
	cout << endl;
}