#ifndef _EDITOR_H
#define _EDITOR_H

#include "Common.h"
#include "GameObject.h"

class Scene;

class Editor
{
public:
	Editor();
	Editor(Scene *tempScene);
	~Editor();
	void readCommand();

private:
	Scene *curScene;
	string curName;
	GameObject *curGameObject;
	Object *curObject;
	Texture *curTexture;
	Shader *curShader;
	
	void assignName();
	void assignGameObject();
	void assignObject();
	void assignTexture();
	void assignShader();
	void spawnObject();
	void setPos();
	void movePos();
};

#endif