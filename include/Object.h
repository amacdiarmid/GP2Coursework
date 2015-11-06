#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include <vector>

class Object
{
public:
	Object();
	~Object();

	void createTexture(string texturePath);
	void createBuffer(string modelPath);
	void cleanUp();
	GLuint getVBO();
	GLuint getEBO();
	GLuint getVAO();
	GLuint getTexture();
	vector<string> *getAttribsList();
	MeshData *getMesh();

private:

};

#endif