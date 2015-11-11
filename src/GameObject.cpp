#include "GameObject.h";

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	name = tempName;
	childrenList.clear();
	componentsList.clear();
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
}

GameObject::~GameObject()
{
}


void GameObject::addComponent(Components type)
{
	if (type == RENDER_COMPONENT)
	{
		cout << "adding render Comp to " << name << endl;
		Renderer renderer = Renderer();
		renderer.setOwner(this);
		componentsList.insert(pair<Components, Component*>(type, &renderer));
	}
	else
	{
		cout << "error_1, gameObject.cpp - no component" << endl;
	}
}

void GameObject::update()
{
	cout << name << " update" << endl;
	if (world == false)
	{
		worldPosition = localPosition + parent->getPosition();
	}
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		i->second->update();
	}
	for (auto i = childrenList.begin(); i != childrenList.end(); i++)
	{
		i->second->update();
	}
}

void GameObject::render()
{
	cout << name << " update" << endl;
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		i->second->render();
	}
	for (auto i = childrenList.begin(); i != childrenList.end(); i++)
	{
		i->second->render();
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

void GameObject::getComponents()
{
	cout << " " << componentsList.size() << endl;
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		cout << i->second->getType() << " ";
	}
	cout << endl;
}