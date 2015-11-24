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



void GameObject::update(mat4 VPMat)
{
	mat4 modelMatrix = translate(mat4(1.0f), localPos);
	modelMatrix = rotate(modelMatrix, radians(rotation.x), vec3(1, 0, 0));
	modelMatrix = rotate(modelMatrix, radians(rotation.y), vec3(0, 1, 0));
	modelMatrix = rotate(modelMatrix, radians(rotation.z), vec3(0, 0, 1));
	modelMatrix = scale(modelMatrix, size);
	MVP = VPMat * modelMatrix;

	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->update(MVP);
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->update(VPMat);
		}
	}
}

void GameObject::render(Fustrum* fustrum)
{
	if (model != NULL)
	{
		positionToFrustrum pos = fustrum->isInFrustrum(model->getBoundingBox(), MVP);
		if (pos == OUTSIDE_FRUSTRUM)
		{
			cout << name << " is outside" << endl;
		}
		else if (pos == INTERSECT_FRUSTRUM)
		{
			cout << name << " is intersected" << endl;
		}
		else
		{
			cout << name << " is inside" << endl;
		}
	}
	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->render();
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->render(fustrum);
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
	localPos += tempPos;
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