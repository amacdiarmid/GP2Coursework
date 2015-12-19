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
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	//set this stuff up into object files 

	//create objects
	objects.insert(pair<string, Object*>("lander", new Object("lander")));
	objects["lander"]->createBuffer("/lander.FBX");
	
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.FBX");

	objects.insert(pair<string, Object*>("teapotRoom", new Object("teapotRoom")));
	objects["teapotRoom"]->createBuffer("/TheTeapotRoom.FBX");
	
	objects.insert(pair<string, Object*>("heroWalker", new Object("heroWalker")));
	objects["heroWalker"]->createBuffer("/heroWalker.FBX");
	objects.insert(pair<string, Object*>("walkerEvo", new Object("walkerEvo")));
	objects["walkerEvo"]->createBuffer("/walkerEvo.FBX");

	//create textures
	textures.insert(pair<string, Texture*>("sun", new Texture("sun")));
	textures["sun"]->createTexture("/SunTexture.png");

	textures.insert(pair<string, Texture*>("lander", new Texture("lander")));
	textures["lander"]->createTexture("/apollo map.jpg");

	textures.insert(pair<string, Texture*>("heroWalker", new Texture("heroWalker")));
	textures["heroWalker"]->createTexture("/unsung-map.jpg");
	textures.insert(pair<string, Texture*>("walkerEvo", new Texture("walkerEvo")));
	textures["walkerEvo"]->createTexture("/walkerMap.jpg");

	textures.insert(pair<string, Texture*>("teapotRoom", new Texture("teapotRoom")));
	textures["teapotRoom"]->createTexture("/teapotRoom.jpg");

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

	//loadScene(worldObject, name, this);

	//uncomment for world reset
	GameObject *tempObj;

	//player
	worldObject->addChild(new GameObject("player", worldObject, input));
	worldObject->getChild("player")->addComponent(INPUT_COMPONENT);

	//skybox
	//david do stuff here


	//empty room node
	worldObject->addChild(new GameObject("emptyRoomNode", worldObject));	//creating node
	worldObject->getChild("emptyRoomNode")->setActive(true);

	//teapot room node done
	worldObject->addChild(new GameObject("teapotRoomNode", worldObject));	//creating node
	tempObj = worldObject->getChild("teapotRoomNode"); //setting temp object for easy access
	tempObj->setPosition(vec3(0, 0, 0));
	tempObj->setActive(false);
	
	tempObj->addChild(new GameObject("sun", tempObj, objects["teapot"], textures["sun"], shaders["main"]));	//creating object
	tempObj->getChild("sun")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("sun")->setPosition(vec3(0, 25, 0));	//changing postiion
	tempObj->getChild("sun")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("sun")->setScale(vec3(0.5, 0.5, 0.5));	//change scele

	tempObj->addChild(new GameObject("teapotRoom", tempObj, objects["teapotRoom"], textures["teapotRoom"], shaders["main"]));	//creating object
	tempObj->getChild("teapotRoom")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("teapotRoom")->setPosition(vec3(0, -25, 0));	//changing postiion
	tempObj->getChild("teapotRoom")->setRotation(vec3(-90, 0, 0));	//change rotaion
	tempObj->getChild("teapotRoom")->setScale(vec3(1, 1, 1));	//change scele


	//lander room node
	worldObject->addChild(new GameObject("apolloRoomNode", worldObject));	//creating node
	tempObj = worldObject->getChild("apolloRoomNode"); //setting temp object for easy access
	tempObj->setActive(false);

	tempObj->addChild(new GameObject("lander", tempObj, objects["lander"], textures["lander"], shaders["main"]));	//creating object
	tempObj->getChild("lander")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("lander")->setPosition(vec3(0, -5, 0));	//changing postiion
	tempObj->getChild("lander")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("lander")->setScale(vec3(1, 1, 1));	//change scele

	//walker room node
	worldObject->addChild(new GameObject("walkerNode", worldObject));	//creating node
	tempObj = worldObject->getChild("walkerNode"); //setting temp object for easy access
	tempObj->setActive(false);

	tempObj->addChild(new GameObject("heroWalker", tempObj, objects["heroWalker"], textures["heroWalker"], shaders["main"]));	//creating object
	tempObj->getChild("heroWalker")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("heroWalker")->setPosition(vec3(0, -35, 0));	//changing postiion
	tempObj->getChild("heroWalker")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("heroWalker")->setScale(vec3(3, 3, 3));	//change scele

	tempObj->addChild(new GameObject("walkerEvo1", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo1")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo1")->setPosition(vec3(0, -23, 60));	//changing postiion
	tempObj->getChild("walkerEvo1")->setRotation(vec3(0, 90, 0));	//change rotaion
	tempObj->getChild("walkerEvo1")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo2", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo2")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo2")->setPosition(vec3(0, -23, 90));	//changing postiion
	tempObj->getChild("walkerEvo2")->setRotation(vec3(0, 90, 0));	//change rotaion
	tempObj->getChild("walkerEvo2")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo3", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo3")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo3")->setPosition(vec3(0, -23, -60));	//changing postiion
	tempObj->getChild("walkerEvo3")->setRotation(vec3(0, -90, 0));	//change rotaion
	tempObj->getChild("walkerEvo3")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo4", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo4")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo4")->setPosition(vec3(0, -23, -90));	//changing postiion
	tempObj->getChild("walkerEvo4")->setRotation(vec3(0, -90, 0));	//change rotaion
	tempObj->getChild("walkerEvo4")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo5", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo5")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo5")->setPosition(vec3(-60, -23, 0));	//changing postiion
	tempObj->getChild("walkerEvo5")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("walkerEvo5")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo6", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo6")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo6")->setPosition(vec3(-90, -23, 0));	//changing postiion
	tempObj->getChild("walkerEvo6")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("walkerEvo6")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo7", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo7")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo7")->setPosition(vec3(60, -23, 0));	//changing postiion
	tempObj->getChild("walkerEvo7")->setRotation(vec3(0, 180, 0));	//change rotaion
	tempObj->getChild("walkerEvo7")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo8", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo8")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo8")->setPosition(vec3(90, -23, 0));	//changing postiion
	tempObj->getChild("walkerEvo8")->setRotation(vec3(0, 180, 0));	//change rotaion
	tempObj->getChild("walkerEvo8")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo9", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo9")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo9")->setPosition(vec3(42, -23, 42));	//changing postiion
	tempObj->getChild("walkerEvo9")->setRotation(vec3(0, 135, 0));	//change rotaion
	tempObj->getChild("walkerEvo9")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo10", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo10")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo10")->setPosition(vec3(63, -23, 63));	//changing postiion
	tempObj->getChild("walkerEvo10")->setRotation(vec3(0, 135, 0));	//change rotaion
	tempObj->getChild("walkerEvo10")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo11", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo11")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo11")->setPosition(vec3(-42, -23, -42));	//changing postiion
	tempObj->getChild("walkerEvo11")->setRotation(vec3(0, -45, 0));	//change rotaion
	tempObj->getChild("walkerEvo11")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo12", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo12")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo12")->setPosition(vec3(-63, -23, -63));	//changing postiion
	tempObj->getChild("walkerEvo12")->setRotation(vec3(0, -45, 0));	//change rotaion
	tempObj->getChild("walkerEvo12")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo13", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo13")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo13")->setPosition(vec3(-42, -23, 42));	//changing postiion
	tempObj->getChild("walkerEvo13")->setRotation(vec3(0, 45, 0));	//change rotaion
	tempObj->getChild("walkerEvo13")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo14", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo14")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo14")->setPosition(vec3(-63, -23, 63));	//changing postiion
	tempObj->getChild("walkerEvo14")->setRotation(vec3(0, 45, 0));	//change rotaion
	tempObj->getChild("walkerEvo14")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo15", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo15")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo15")->setPosition(vec3(42, -23, -42));	//changing postiion
	tempObj->getChild("walkerEvo15")->setRotation(vec3(0, 225, 0));	//change rotaion
	tempObj->getChild("walkerEvo15")->setScale(vec3(2, 2, 2));	//change scele

	tempObj->addChild(new GameObject("walkerEvo16", tempObj, objects["walkerEvo"], textures["walkerEvo"], shaders["main"]));	//creating object
	tempObj->getChild("walkerEvo16")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerEvo16")->setPosition(vec3(63, -23, -63));	//changing postiion
	tempObj->getChild("walkerEvo16")->setRotation(vec3(0, 225, 0));	//change rotaion
	tempObj->getChild("walkerEvo16")->setScale(vec3(2, 2, 2));	//change scele




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
	case SDLK_1:
		cout << "set empty room" << endl;
		worldObject->getChild("emptyRoomNode")->setActive(true);
		worldObject->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_2:
		cout << "set teapot room" << endl;
		worldObject->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("teapotRoomNode")->setActive(true);
		worldObject->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_3:
		cout << "set old room" << endl;
		worldObject->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("apolloRoomNode")->setActive(true);
		worldObject->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_4:
		cout << "set scifi room" << endl;
		worldObject->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("walkerNode")->setActive(true);
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
