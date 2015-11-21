#include "Scene.h"

Scene::Scene()
{
	debugMode = false;
}

Scene::Scene(string tempName)
{
	debugMode = false;
	name = tempName;
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

	glUseProgram(shaders["main"]->getShader());

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(shaders["main"]->getShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(player->getMVPmatrix()));

	worldObject->render();

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}

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

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in updating scene " << err << endl;
	}
}

void Scene::createScene()
{
	editor = new Editor(this);
	debugMode = false;

	//create objects
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.fbx");

	//create textures
	textures.insert(pair<string, Texture*>("sun", new Texture("sun")));
	textures["sun"]->createTexture("/SunTexture.png");
	textures.insert(pair<string, Texture*>("earth", new Texture("earth")));
	textures["earth"]->createTexture("/EarthTexture.png");
	textures.insert(pair<string, Texture*>("moon", new Texture("moon")));
	textures["moon"]->createTexture("/MoonTexture.png");

	//create shaders
	shaders.insert(pair<string, Shader*>("main", new Shader("main")));
	shaders["main"]->attatchVertexShader("/textureVS.glsl");
	shaders["main"]->attatchFragmentShader("/textureFS.glsl");
	shaders["main"]->createShader();

	//create player/debug cam
	player = new PlayerController();

	//add scene graph. this could be an external file or another function but it is here for now 
	
	loadScene(worldObject, name, this);

	//worldObject->addChild(new GameObject("sun", worldObject, objects["teapot"], textures["sun"], shaders["main"]));
	//worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	//worldObject->getChild("sun")->addChild(new GameObject("earth", worldObject, objects["teapot"], textures["earth"], shaders["main"]));
	//worldObject->getChild("sun")->getChild("earth")->addComponent(RENDER_COMPONENT);

	//worldObject->getChild("sun")->getChild("earth")->addChild(new GameObject("moon", worldObject, objects["teapot"], textures["moon"], shaders["main"]));
	//worldObject->getChild("sun")->getChild("earth")->getChild("moon")->addComponent(RENDER_COMPONENT);

	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->printComponents();
	worldObject->printChildern();

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating scene " << err << endl;
	}	
}

void Scene::destroyScene()
{
	shaders["main"]->cleanUp();
	objects["teapot"]->cleanUp();
}

void Scene::SceneLoop()
{
	update();
	render();
}

GameObject *Scene::getGameObject(string command)
{
	GameObject * tempGameObject;
	tempGameObject = worldObject->findChild(command);
	if (tempGameObject != NULL)
	{
		cout << "game object assigned " << tempGameObject->getName() << endl;
	}
	else
	{
		cout << "game object assigned NULL"  << endl;
	}
	return tempGameObject;
}

GameObject *Scene::getWorldObject()
{
	return worldObject;
}


Object *Scene::getObject(string command)
{
	Object * tempObject;
	tempObject = objects[command];
	if (tempObject != NULL)
	{
		cout << "mesh assigned " << tempObject->getName() << endl;
	}
	else
	{
		cout << "mesh assigned NULL" << endl;
	}
	return tempObject;
}

Texture *Scene::getTexture(string command)
{
	Texture * tempTexture;
	tempTexture = textures[command];
	if (tempTexture != NULL)
	{
		cout << "texture assigned " << tempTexture->getName() << endl;
	}
	else
	{
		cout << "texture assigned NULL" << endl;		
	}
	return tempTexture;
}

Shader *Scene::getShader(string command)
{
	Shader * tempShader;
	tempShader = shaders[command];
	if (tempShader != NULL)
	{
		cout << "shader assigned " << tempShader->getName() << endl;
	}
	else
	{
		cout << "shader assigned NULL" << endl;
	}
	return tempShader;
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
	case SDLK_m:
		//set world object to active or not
		break;
	default:
		break;
	}
}
void Scene::onkeyUp(SDL_Keycode key)
{
	cout << "Key up " << key << endl;
}

string Scene::getName()
{
	return name;
}
