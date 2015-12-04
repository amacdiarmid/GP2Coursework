#include "HoloRoomScene.h"
#include "Editor.h"

//int i = 0;

HoloRoomScene::HoloRoomScene()
{
	debugMode = false;
	worldObject = new GameObject("world Object");
}

HoloRoomScene::HoloRoomScene(string tempName)
{
	debugMode = false;
	name = tempName;
	worldObject = new GameObject("world Object");
}

HoloRoomScene::~HoloRoomScene()
{
}

void HoloRoomScene::render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	worldObject->render(fustrum);

	/*
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}
	*/
}

void HoloRoomScene::update()
{
	input->Update();

	//i ++;
	//worldObject->getChild("sun")->setRotation(vec3(0, i, 0));
	//worldObject->getChild("sun")->getChild("earth")->setRotation(vec3(0, i, 0));
	//worldObject->getChild("sun")->getChild("earth")->getChild("moon")->changePosition(vec3(0.0f, 0.0f, -0.01f));

	worldObject->update(input->getMVPmatrix());

	/*
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in updating scene " << err << endl;
	}
	*/
}

void HoloRoomScene::createScene()
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
	input = new PlayerController();
	fustrum = new Fustrum(input);
	fustrum->setUpCamera();
	fustrum->updateCamera();
	worldObject->setScene(this);

	//add scene graph. this could be an external file or another function but it is here for now 

	loadScene(worldObject, name, this);

	//uncomment for world reset

	//worldObject->addChild(new GameObject("player", worldObject, input));
	//worldObject->getChild("player")->addComponent(INPUT_COMPONENT);

	//worldObject->addChild(new GameObject("sun", worldObject, objects["teapot"], textures["sun"], shaders["main"]));
	//worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	//worldObject->getChild("sun")->addChild(new GameObject("earth", worldObject, objects["teapot"], textures["earth"], shaders["main"]));
	//worldObject->getChild("sun")->getChild("earth")->addComponent(RENDER_COMPONENT);
	//worldObject->getChild("sun")->getChild("earth")->changePosition(vec3(25, 0, 0));

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

void HoloRoomScene::destroyScene()
{
	shaders["main"]->cleanUp();
	objects["teapot"]->cleanUp();
}

void HoloRoomScene::SceneLoop()
{
	windowLoop();
	update();
	render();
}

GameObject *HoloRoomScene::getGameObject(string command)
{
	GameObject * tempGameObject;
	tempGameObject = worldObject->findChild(command);
	if (tempGameObject != NULL)
	{
		cout << "game object assigned " << tempGameObject->getName() << endl;
	}
	else
	{
		cout << "game object assigned NULL" << endl;
	}
	return tempGameObject;
}

GameObject *HoloRoomScene::getWorldObject()
{
	return worldObject;
}


Object *HoloRoomScene::getObject(string command)
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

Texture *HoloRoomScene::getTexture(string command)
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

Shader *HoloRoomScene::getShader(string command)
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


void HoloRoomScene::onKeyDown(SDL_Keycode key)
{
	cout << "Key down " << key << endl;
	fustrum->updateCamera();
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
		input->setDebug(debugMode);
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
void HoloRoomScene::onkeyUp(SDL_Keycode key)
{
	cout << "Key up " << key << endl;
}

void HoloRoomScene::mouseMove(SDL_MouseMotionEvent motion)
{

}

string HoloRoomScene::getName()
{
	return name;
}
