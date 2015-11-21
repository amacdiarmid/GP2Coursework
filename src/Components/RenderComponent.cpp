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

void Renderer::update()
{

}

void Renderer::render()
{
	//get the uniform for the movementVec
	GLint moveVecLocation = glGetUniformLocation(owner->getShader()->getShader(), "movementVec");
	glUniform3fv(moveVecLocation, 1, value_ptr(owner->getWorldPos()));

	//get the uniform for the texture coords
	GLint texture0Location = glGetUniformLocation(owner->getShader()->getShader(), "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *owner->getTexture()->getTexture());
	glUniform1i(texture0Location, 0);

	glBindVertexArray(owner->getModel()->getVAO());
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, owner->getModel()->getMesh()->getNumIndices(), GL_UNSIGNED_INT, 0);
}

string Renderer::getType()
{
	return type;
}