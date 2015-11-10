#include "GameObject.h";

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	name = tempName;
	children.clear();
	components.clear();
}

GameObject::GameObject(string tempName, GameObject *tempParent, Object *tempModel, GLuint *tempTexture, Shader *tempShader)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = tempModel;
	texture = tempTexture;
	shader = tempShader;
	children.clear();
	components.clear();
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
		components.push_back(renderer);
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
	if (!components.empty())
	{
		for each (Component var in components)
		{
			var.update();
		}
	}
	if (!children.empty())
	{
		for each (GameObject var in children)
		{
			var.update();
		}
	}
}

void GameObject::render()
{
	cout << name << " update" << endl;
	for each (Component var in components)
	{
		var.render();
	}
	for each (GameObject var in children)
	{
		var.render();
	}
}

vec3 GameObject::getPosition()
{
	return worldPosition;
}

void GameObject::addChild(GameObject *tempChild)
{
	children.push_back(*tempChild);
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

GameObject *GameObject::getLastChild()
{
	return &children.back();
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
	for each (GameObject var in children)
	{
		cout << "object: " << var.getName() << " components ";
		var.getComponents();
		var.getChildern();
	}
}

void GameObject::getComponents()
{
	for each (Component var in components)
	{
		cout << var.getType() << " ";
	}
	cout << endl;
}