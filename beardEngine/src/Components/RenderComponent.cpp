#include "Components\RenderComponent.h"
#include "GameObject.h"

Renderer::Renderer()
{
	type = "render component";
}

Renderer::Renderer(GameObject *tempOwner)
{
	type = "render component";
	owner = tempOwner;
}

Renderer::~Renderer()
{
}

void Renderer::init()
{

}

void Renderer::update(mat4 MVPMat)
{
	MVP = MVPMat;
}

void Renderer::render()
{
	if (owner->getCurScene()->getActiveShader() != owner->getShader()->getShader())
	{
		glUseProgram(owner->getShader()->getShader());
		owner->getCurScene()->setActiveShader(owner->getShader()->getShader());
	}

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in changing shader " << err << endl;
	}

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_FALSE);
	}

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in enabling depth mask " << err << endl;
	}

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(owner->getShader()->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));

	err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in assigning mvp " << err << endl;
	}
	
	if (owner->getTexture()->getTex2D())
	{
		//get the uniform for the texture coords
		GLint texture0Location = glGetUniformLocation(owner->getShader()->getShader(), "texture0");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, owner->getTexture()->getTexture());
		glUniform1i(texture0Location, 0);
		
		err = GL_NO_ERROR;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			//Process/log the error.
			cout << "error in assigning texture" << err << endl;
		}
	}
	else
	{
		GLint cubeTexLocation = glGetUniformLocation(owner->getShader()->getShader(), "cubeTexture");
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, owner->getTexture()->getTexture());
		glUniform1i(cubeTexLocation, 1);
	}

	glBindVertexArray(owner->getModel()->getVAO());
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, owner->getModel()->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);

	if (!owner->getTexture()->getTex2D())
	{
		glDepthMask(GL_TRUE);
	}

}

string Renderer::getType()
{
	return type;
}