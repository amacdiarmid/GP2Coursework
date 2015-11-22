#include "GameObject.h";

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	name = tempName;
	parent = NULL;
	model = NULL;
	texture = NULL;
	shader = NULL;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent, Object *tempModel, Texture *tempTexture, Shader *tempShader)
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



void GameObject::update(mat4 MVPMat)
{
	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->update(MVPMat);
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->update(MVPMat);
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

void GameObject::addChild(GameObject *tempChild)
{
	childrenList.insert(pair<string, GameObject*>(tempChild->getName(), tempChild));
}

void GameObject::changePosition(vec3 tempPos)
{
	worldPos += tempPos;
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
			return child.second->findChild(com);
		}
	}
	return NULL;
}

void GameObject::printChildern()
{
	cout << "\t";

	for (auto i = childrenList.begin(); i != childrenList.end(); i++)
	{
		cout << "object: " << i->second->getName() << " components ";
		i->second->printComponents();
		i->second->printChildern();
	}
}

void GameObject::printComponents()
{
	cout << " " << componentsList.size() << " ";
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		cout << i->second->getType() << " ";
	}
	cout << endl;
}