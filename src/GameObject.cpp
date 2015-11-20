#include "GameObject.h";

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	parent = NULL;
	name = tempName;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent, Object *tempModel, GLuint *tempTexture, Shader *tempShader)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = tempModel;
	texture = tempTexture;
	shader = tempShader;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::~GameObject()
{
}


void GameObject::addComponent(Components type)
{
	if (type == RENDER_COMPONENT)
	{
		cout << "adding render Comp to " << name <<  endl;
		componentsList.insert(pair<Components, Component*>(type, new Renderer(this)));
	}
	else
	{
		cout << "error_1, gameObject.cpp - no component" << endl;
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

GameObject *GameObject::findChild(string com)
{
	for each (auto child in childrenList)
	{
		if (child.first == com)
		{
			return child.second;
		}
		else
		{
			child.second->findChild(com);
		}
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