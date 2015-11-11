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
//add a .h file with all the components
#include "Components\BaseComponent.h"
#include "Components\RenderComponent.h"

class Scene
{
public:
	Scene();
	~Scene();
	void update();
	void render();
	void createScene();
	void destroyScene();
	void SceneLoop();

private:
	//matrices
	mat4 viewMatrix;
	mat4 projMatrix;
	mat4 worldMatrix;
	mat4 MVPMatrix;

	//move object
	vec3 movementVec = vec3(0.0f, 0.0f, 0.0f);
	//move camera 
	vec3 worldPoint = vec3(0.0f, 0.0f, 10.0f);
	vec3 lookAtPoint = vec3(0.0f, 0.0f, 0.0f);

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

};

#endif
