#include "Object.h"

MeshData *currentMesh;

GLuint VBO;
GLuint EBO;
GLuint VAO;

GLuint textureMap;

Object::Object()
{
}

Object::~Object()
{
}

void Object::createTexture(string texturePath)
{
	//load texture & bind
	string Path = ASSET_PATH + TEXTURE_PATH + texturePath;
	textureMap = loadTextureFromFile(Path);

	glBindTexture(GL_TEXTURE_2D, textureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Object::createBuffer(string modelPath)
{
	//load model
	currentMesh = new MeshData();
	string Path = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	loadFBXFromFile(Path, currentMesh);

	//gen vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create vertex buffer object
	glGenBuffers(1, &VBO);
	//make the VBO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, currentMesh->getNumVerts()*sizeof(Vertex), currentMesh->vertices.data(), GL_STATIC_DRAW);

	//create element buffer object 
	glGenBuffers(1, &EBO);
	//make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//copy the index date to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentMesh->getNumIndices()*sizeof(int), currentMesh->indices.data(), GL_STATIC_DRAW);

	//tell the shader that 0 is the position element 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	//send the colour to the shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	//send the text coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));
	//send normals to buffer
	glDisableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4) + sizeof(vec2)));
}

void Object::cleanUp()
{
	glDeleteTextures(1, &textureMap);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

GLuint Object::getVBO()
{
	return VBO;
}

GLuint Object::getEBO()
{
	return EBO;
}

GLuint Object::getVAO()
{
	return VAO;
}

GLuint *Object::getTexture()
{
	return &textureMap;
}

MeshData *Object::getMesh()
{
	return currentMesh;
}