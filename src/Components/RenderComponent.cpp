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
	mat4 tempMat = translate(mat4(1.0f), owner->getLocalPos());
	tempMat = rotate(tempMat, radians(owner->getRotation().x), vec3(1, 0, 0));
	tempMat = rotate(tempMat, radians(owner->getRotation().y), vec3(0, 1, 0));
	tempMat = rotate(tempMat, radians(owner->getRotation().z), vec3(0, 0, 1));
	tempMat = scale(tempMat, owner->getScale());
	MVP = MVPMat * tempMat;
}

void Renderer::render()
{
	glUseProgram(owner->getShader()->getShader());

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(owner->getShader()->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVP));

	//get the uniform for the movementVec
	GLint moveVecLocation = glGetUniformLocation(owner->getShader()->getShader(), "movementVec");
	glUniform3fv(moveVecLocation, 1, value_ptr(owner->getLocalPos()));

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