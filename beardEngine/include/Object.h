#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "Box.h"

class Object
{
public:
	Object();
	Object(string tempName);
	~Object();

	void createBuffer(string modelPath);
	void cleanUp();
	GLuint getVBO();
	GLuint getEBO();
	GLuint getVAO();
	MeshData *getMesh();
	string getName();
	Box *getBoundingBox(){ return boundingBox; };

private:
	MeshData *currentMesh;
	Box *boundingBox;

	string name;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

};

#endif