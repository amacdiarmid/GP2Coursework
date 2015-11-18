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



class Scene : public IkeyboardListener
{
public:
	Scene();
	~Scene();
	void update();
	void render();
	void createScene();
	void destroyScene();
	void SceneLoop();

	//debug stuff
	GameObject *getGameObject(string command);
	Object *getObject(string command);
	Texture *getTexture(string command);
	Shader *getShader(string command);

	void onKeyDown(SDL_Keycode key);
	void onkeyUp(SDL_Keycode key);
private:
	PlayerController *player;

	//main gameobject 
	GameObject *worldObject = new GameObject("world Object");
	//game obejcts
	Object *teapotObj;
	
	//textures 
	Texture *sunText;
	Texture *earthText;
	Texture *moonText;
	
	//shaders
	Shader *mainShader;

	//debug mode stuff
	Editor *editor;
	bool debugMode;

};

#endif
