#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(mainShader->getShader());

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(mainShader->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));

	worldObject->render();

}

void Scene::update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	viewMatrix = lookAt(worldPoint, lookAtPoint, vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	MVPMatrix = projMatrix*viewMatrix*worldMatrix;

	worldObject->update();
}

void Scene::createScene()
{
	//create objects
	teapot = new Object();
	teapot->createBuffer("/utah-teapot.fbx");

	//create textures
	teapot->createTexture("/Texture.png");

	//create shaders
	mainShader = new Shader();
	mainShader->attatchVertexShader("/textureVS.glsl");
	mainShader->attatchFragmentShader("/textureFS.glsl");
	mainShader->createShader();

	//create player/debug cam

	//add scene graph. this could be an external file or another function but it is here for now 
	worldObject->addChild(new GameObject("sun", worldObject, teapot, teapot->getTexture(), mainShader));
	worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->getComponents();
	worldObject->getChildern();
}

void Scene::destroyScene()
{
	mainShader->cleanUp();
	teapot->cleanUp();	
}

void Scene::SceneLoop()
{
	update();
	render();
}