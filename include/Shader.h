#ifndef Shader_h
#define Shader_h

#include "Common.h"

enum SHADER_TYPE
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

GLuint loadShaderFromMemory(const char *pMem, SHADER_TYPE shaderType);
GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType);
bool checkForCompilerErrors(GLuint shaderProgram);
bool checkForLinkErrors(GLuint program);

class Shader
{
public:
	Shader();
	~Shader();

	void attatchVertexShader(string shaderPath);
	void attatchFragmentShader(string shaderPath);
	void createShader();
	GLuint getShader();
	void cleanUp();

private:

};

#endif