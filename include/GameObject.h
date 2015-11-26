#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#pragma once

#include "Common.h"
#include "Components\Components.h"
#include "Shader.h"
#include "Object.h"
#include <map>
#include "PlayerController.h"

class GameObject
{
public:
	GameObject();
	GameObject(string tempName);
	GameObject(string tempName,GameObject *tempParent, Object *tempModel, GLuint *tempTexture, Shader *tempShader, PlayerController *tempInput);
	~GameObject();

	void addComponent(Components type);
	void update();
	void render();
	vec3 getPosition();
	void addChild(GameObject *tempChild);
	Object *getModel();
	Shader *getShader();
	GLuint *getTexture();
	PlayerController *getInput();
	GameObject *getChild(string tempName);
	void setPosition(vec3 TempPos);
	void changePosition(vec3 tempPos);
	string getName();
	void getChildern();
	void getComponents();
private:
	string name;
	GameObject *parent;
	bool world;
	bool active;
	map<string, GameObject*> childrenList;
	map<Components, Component*> componentsList;
	Object *model;
	GLuint *texture;
	Shader *shader;
	PlayerController *input;

	//the world position 
	vec3 worldPosition = vec3(0.0f, 0.0f, 0.0f);
	//the distance from the parent world position
	vec3 localPosition = vec3(0.0f, 0.0f, 0.0f);
};

#endif