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

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(owner->getShader()->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));

	//get the uniform for the texture coords
	GLint texture0Location = glGetUniformLocation(owner->getShader()->getShader(), "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *owner->getTexture()->getTexture());
	glUniform1i(texture0Location, 0);

	GLint toonShadeLocation = glGetUniformLocation(owner->getShader()->getShader(), "toonShade");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, *owner->getTexture()->getTexture());
	glUniform1i(toonShadeLocation, 1);

	glBindVertexArray(owner->getModel()->getVAO());
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, owner->getModel()->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
}

string Renderer::getType()
{
	return type;
}