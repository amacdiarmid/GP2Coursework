#include "Scene.h"

Scene::Scene()
{
	debugMode = false;
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
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(player->getMVPmatrix()));

	worldObject->render();

}

void Scene::update()
{
	//SDL_Event event;
	//while (SDL_PollEvent(&event))
	//{
	//	cout << "2" << endl;
	//	switch (event.key.keysym.sym)
	//	{
	//		cout << "3" << endl;
	//	case SDLK_p:
	//		cout << "4" << endl;
	//		if (debugMode)
	//		{
	//			cout << "debug mode off" << endl;
	//			debugMode = false;
	//		}
	//		else
	//		{
	//			cout << "debug mode on" << endl;
	//			debugMode = true;
	//		}
	//	case SDLK_l:
	//		if (debugMode)
	//		{
	//			editor->readCommand();
	//		}
	//	default:
	//		break;
	//	}
	//}

	player->Update();

	/*
	worldObject->getChild("sun")->changePosition(vec3(0.01f, 0.0f, 0.0f));
	worldObject->getChild("sun")->getChild("earth")->changePosition(vec3(0.0f, 0.01f, 0.0f));
	worldObject->getChild("sun")->getChild("earth")->getChild("moon")->changePosition(vec3(0.0f, 0.0f, -0.01f));
	*/

	worldObject->setPosition(player->GetMovementVec());
	worldObject->update();
}

void Scene::createScene()
{
	editor = new Editor(this);
	debugMode = false;

	//create objects
	teapotObj = new Object("teapot");
	teapotObj->createBuffer("/utah-teapot.fbx");

	//create textures
	sunText = new Texture("sun");
	sunText->createTexture("/SunTexture.png");
	earthText = new Texture("earth");
	earthText->createTexture("/EarthTexture.png");
	moonText = new Texture("moon");
	moonText->createTexture("/MoonTexture.png");

	//create shaders
	mainShader = new Shader("main");
	mainShader->attatchVertexShader("/textureVS.glsl");
	mainShader->attatchFragmentShader("/textureFS.glsl");
	mainShader->createShader();

	//create player/debug cam
	player = new PlayerController();

	//add scene graph. this could be an external file or another function but it is here for now 
	
	/*
	worldObject->addChild(new GameObject("sun", worldObject, teapotObj, sunText->getTexture(), mainShader));
	worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	worldObject->getChild("sun")->addChild(new GameObject("earth", worldObject->getChild("sun"), teapotObj, earthText->getTexture(), mainShader));
	worldObject->getChild("sun")->getChild("earth")->addComponent(RENDER_COMPONENT);

	worldObject->getChild("sun")->getChild("earth")->addChild(new GameObject("moon", worldObject->getChild("sun")->getChild("earth"), teapotObj, moonText->getTexture(), mainShader));
	worldObject->getChild("sun")->getChild("earth")->getChild("moon")->addComponent(RENDER_COMPONENT);

	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->getComponents();
	worldObject->getChildern();
	*/	
}

void Scene::destroyScene()
{
	mainShader->cleanUp();
	teapotObj->cleanUp();
}

void Scene::SceneLoop()
{
	update();
	render();
}

GameObject *Scene::getGameObject(string command)
{
	return worldObject;
}

Object *Scene::getObject(string command)
{
	return teapotObj;
}

Texture *Scene::getTexture(string command)
{
	return sunText;
}

Shader *Scene::getShader(string command)
{
	return mainShader;
}


void Scene::onKeyDown(SDL_Keycode key)
{
	cout << "Key down " << key << endl;
	switch (key)
	{
	case SDLK_p:
		if (debugMode)
		{
			cout << "debug mode off" << endl;
			debugMode = false;
		}
		else
		{
			cout << "debug mode on" << endl;
			debugMode = true;
		}
		break;
	case SDLK_l:
		if (debugMode)
		{
			editor->readCommand();
		}
		break;
	default:
		break;
	}
}
void Scene::onkeyUp(SDL_Keycode key)
{
	cout << "Key up " << key << endl;
}
