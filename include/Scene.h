#ifndef _SCENE_H_
#define _SCENE_H_

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "Object.h"

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
