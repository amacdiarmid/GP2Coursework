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
	void createScene();
	void destroyScene();
	void SceneLoop();

private:

};

#endif
