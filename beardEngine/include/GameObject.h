#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#pragma once

#include "Common.h"
#include "Components\Components.h"
#include "Shader.h"
#include "Object.h"
#include <map>
#include "ViewFrustumCulling.h"

class GameObject
{
public:
	GameObject();
	GameObject(string tempName);
	GameObject(string tempName, GameObject *tempParent, Object *tempModel, Texture *tempTexture, Shader *tempShader);
	~GameObject();

	//in .cpp
	void update(mat4 VPMat);
	void render(Fustrum *fustrum);
	void addComponent(Components type);
	void addChild(GameObject *tempChild);
	void changePosition(vec3 tempPos);
	GameObject *findChild(string com);
	void printChildern();
	void printComponents();

	//getters
	vec3 getLocalPos(){ return localPos; };
	vec3 getScale(){ return size; };
	vec3 getRotation(){ return rotation; };
	Object *getModel(){ return model; };
	Shader *getShader(){ return shader; };
	Texture *getTexture(){ return texture; };
	GameObject *getChild(string tempName) { return childrenList[tempName]; };
	string getName(){ return name; };
	map<string, GameObject*> *getChildrenMap(){ return &childrenList; };
	map<Components, Component*> *getCompMap(){ return &componentsList; };
	bool getActive(){ return active; };
	bool getWorld(){ return world; };

	//setters
	void setScale(vec3 tempScale){ size = tempScale; };
	void setRotation(vec3 tempRotation){ rotation = tempRotation; };
	void setModel(Object* tempModel) { model = tempModel; };
	void setShader(Shader* tempShader){ shader = tempShader; };
	void setTexture(Texture* tempTexture){ texture = tempTexture; };
	void setPosition(vec3 TempPos){ localPos = TempPos; };
	void setName(string tempName){ name = tempName; };
	void setParent(GameObject* tempParent){ parent = tempParent; };
	void setWord(bool tempBool){ world = tempBool; };
	void setActive(bool tempBool){ active = tempBool; };
private:
	string name;
	GameObject *parent;
	bool world;
	bool active;
	map<string, GameObject*> childrenList;
	map<Components, Component*> componentsList;
	Object *model;
	Texture *texture;
	Shader *shader;
	mat4 MVP;

	//the distance from the parent world position
	vec3 localPos = vec3(0.0f, 0.0f, 0.0f);
	//scale
	vec3 size = vec3(1.0f, 1.0f, 1.0f);
	//rotation
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
};

#endif