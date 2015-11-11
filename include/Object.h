#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"

class Object
{
public:
	Object();
	~Object();

	void createBuffer(string modelPath);
	void cleanUp();
	GLuint getVBO();
	GLuint getEBO();
	GLuint getVAO();
	MeshData *getMesh();

private:
	MeshData *currentMesh;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

};

#endif