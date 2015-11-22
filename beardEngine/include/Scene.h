#ifndef _SCENE_H_
#define _SCENE_H_

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "Object.h"
#include "GameObject.h"
#include "Components\Components.h"
#include "Editor.h"
#include "SDL2.h"
#include "KeyboardListener.h"
#include "PlayerController.h"
#include <map>

class Scene : public IkeyboardListener
{
public:
	Scene();
	Scene(string tempName);
	~Scene();
	void update();
	void render();
	void createScene();
	void destroyScene();
	void SceneLoop();

	//debug stuff
	GameObject *getGameObject(string command);
	GameObject *getWorldObject();
	Object *getObject(string command);
	Texture *getTexture(string command);
	Shader *getShader(string command);
	string getName();

	void onKeyDown(SDL_Keycode key);
	void onkeyUp(SDL_Keycode key);
private:
	string name;

	PlayerController *player;

	//main gameobject 
	GameObject *worldObject = new GameObject("world Object");
	
	//game objects
	map<string, Object*> objects;
	
	//textures 
	map<string, Texture*> textures;
	
	//shaders
	map<string, Shader*> shaders;

	//debug mode stuff
	Editor *editor;
	bool debugMode;

};

#endif
