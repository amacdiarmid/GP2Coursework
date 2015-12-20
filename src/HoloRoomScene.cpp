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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	
	glDepthMask(GL_TRUE);
	
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

	input = new PlayerController();


	//create cubemap texture
	skyMaterial = new CubeTexture("skybox");
	string skyBoxFront = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_front.png";
	string skyBoxBack = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_back.png";
	string skyBoxLeft = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_left.png";
	string skyBoxRight = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_right.png";
	string skyBoxTop = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_top.png";
	string skyBoxBottom = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_bottom.png";
	skyMaterial->loadSkyBoxTextures(skyBoxFront, skyBoxBack, skyBoxLeft, skyBoxRight, skyBoxTop, skyBoxBottom);

	//create objects
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.fbx");
	objects.insert(pair<string, Object*>("holoRoom", new Object("holoRoom")));
	objects["holoRoom"]->createBuffer("/Holodome.FBX");
	objects.insert(pair<string, Object*>("lander", new Object("lander")));
	objects["lander"]->createBuffer("/lander.FBX");

	objects.insert(pair<string, Object*>("heroWalker", new Object("heroWalker")));
	objects["heroWalker"]->createBuffer("/heroWalker.FBX");
	objects.insert(pair<string, Object*>("walkerEvo", new Object("walkerEvo")));
	objects["walkerEvo"]->createBuffer("/walkerEvo.FBX");

	objects.insert(pair<string, Object*>("cubeMesh", new Cube("cubeMesh")));
	objects["cubeMesh"]->createBuffer();

	//create textures
	textures.insert(pair<string, Texture*>("sun", new Texture("sun")));
	textures["sun"]->createTexture("/SunTexture.png");
	textures.insert(pair<string, Texture*>("mercury", new Texture("mercury")));
	textures["mercury"]->createTexture("/MercuryTexture.png");
	textures.insert(pair<string, Texture*>("venus", new Texture("venus")));
	textures["venus"]->createTexture("/VenusTexture.png");
	textures.insert(pair<string, Texture*>("earth", new Texture("earth")));
	textures["earth"]->createTexture("/EarthTexture.png");
	textures.insert(pair<string, Texture*>("moon", new Texture("moon")));
	textures["moon"]->createTexture("/MoonTexture.png");
	textures.insert(pair<string, Texture*>("mars", new Texture("mars")));
	textures["mars"]->createTexture("/MarsTexture.png");
	textures.insert(pair<string, Texture*>("jupiter", new Texture("jupiter")));
	textures["jupiter"]->createTexture("/JupiterTexture.png");
	textures.insert(pair<string, Texture*>("saturn", new Texture("saturn")));
	textures["saturn"]->createTexture("/SaturnTexture.png");
	textures.insert(pair<string, Texture*>("uranus", new Texture("uranus")));
	textures["uranus"]->createTexture("/UranusTexture.png");
	textures.insert(pair<string, Texture*>("neptune", new Texture("neptune")));
	textures["neptune"]->createTexture("/NeptuneTexture.png");
	textures.insert(pair<string, Texture*>("pluto", new Texture("pluto")));
	textures["pluto"]->createTexture("/PlutoTexture.png");

	textures.insert(pair<string, Texture*>("wall", new Texture("wall")));
	textures["wall"]->createTexture("/wallTexture.png");

	textures.insert(pair<string, Texture*>("lander", new Texture("lander")));
	textures["lander"]->createTexture("/apollo map.jpg");

	textures.insert(pair<string, Texture*>("heroWalker", new Texture("heroWalker")));
	textures["heroWalker"]->createTexture("/unsung-map.jpg");
	textures.insert(pair<string, Texture*>("walkerEvo", new Texture("walkerEvo")));
	textures["walkerEvo"]->createTexture("/walkerMap.jpg");

	//create shaders
	shaders.insert(pair<string, Shader*>("main", new Shader("main")));
	shaders["main"]->attatchVertexShader("/textureVS.glsl");
	shaders["main"]->attatchFragmentShader("/textureFS.glsl");
	shaders["main"]->createShader();

	shaders.insert(pair<string, Shader*>("sky", new Shader("sky")));
	shaders["sky"]->attatchVertexShader("/skyboxVS.glsl");
	shaders["sky"]->attatchFragmentShader("/skyboxFS.glsl");
	shaders["sky"]->createShader();


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

	//main room
	worldObject->addChild(new GameObject("room", worldObject, objects["holoRoom"], textures["wall"], shaders["main"]));	//creating object
	worldObject->getChild("room")->addComponent(RENDER_COMPONENT);	//adding render comp
	worldObject->getChild("room")->changePosition(vec3(0, -25, 0));	//changing position

	//empty room node
	worldObject->getChild("room")->addChild(new GameObject("emptyRoomNode", worldObject->getChild("room")));	//creating node
	worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(true);

	//teapot room node done
	worldObject->getChild("room")->addChild(new GameObject("teapotRoomNode", worldObject->getChild("room")));	//creating node
	tempObj = worldObject->getChild("room")->getChild("teapotRoomNode"); //setting temp object for easy access
	tempObj->setPosition(vec3(0, 0, 0));
	tempObj->setActive(false);
	
	tempObj->addChild(new GameObject("sun", tempObj, objects["teapot"], textures["sun"], shaders["main"]));	//creating object
	tempObj->getChild("sun")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("sun")->setPosition(vec3(0, 25, 0));	//changing postiion
	tempObj->getChild("sun")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("sun")->setScale(vec3(0.5, 0.5, 0.5));	//change scele

	tempObj->addChild(new GameObject("mercury", tempObj, objects["teapot"], textures["mercury"], shaders["main"]));	//creating object
	tempObj->getChild("mercury")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("mercury")->setPosition(vec3(15, 20, 0));	//changing postiion
	tempObj->getChild("mercury")->setRotation(vec3(10, 10, 10));	//change rotaion
	tempObj->getChild("mercury")->setScale(vec3(0.25, 0.25, 0.25));	//change scele

	tempObj->addChild(new GameObject("venus", tempObj, objects["teapot"], textures["venus"], shaders["main"]));	//creating object
	tempObj->getChild("venus")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("venus")->setPosition(vec3(25, 15, 25));	//changing postiion
	tempObj->getChild("venus")->setRotation(vec3(20, 20, 20));	//change rotaion
	tempObj->getChild("venus")->setScale(vec3(0.3, 0.3, 0.3));	//change scele

	tempObj->addChild(new GameObject("earth", tempObj, objects["teapot"], textures["earth"], shaders["main"]));	//creating object
	tempObj->getChild("earth")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("earth")->setPosition(vec3(0, 30, 30));	//changing postiion
	tempObj->getChild("earth")->setRotation(vec3(30, 30, 30));	//change rotaion
	tempObj->getChild("earth")->setScale(vec3(0.35, 0.35, 0.35));	//change scele

	tempObj->addChild(new GameObject("moon", tempObj->getChild("earth"), objects["teapot"], textures["moon"], shaders["main"]));	//creating object
	tempObj->getChild("moon")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("moon")->setPosition(vec3(5, 35, 15));	//changing postiion
	tempObj->getChild("moon")->setRotation(vec3(40, 40, 40));	//change rotaion
	tempObj->getChild("moon")->setScale(vec3(0.25, 0.25, 0.25));	//change scele

	tempObj->addChild(new GameObject("mars", tempObj, objects["teapot"], textures["mars"], shaders["main"]));	//creating object
	tempObj->getChild("mars")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("mars")->setPosition(vec3(45, 25, 50));	//changing postiion
	tempObj->getChild("mars")->setRotation(vec3(0, 0, 90));	//change rotaion
	tempObj->getChild("mars")->setScale(vec3(0.35, 0.35, 0.35));	//change scele

	tempObj->addChild(new GameObject("jupiter", tempObj, objects["teapot"], textures["jupiter"], shaders["main"]));	//creating object
	tempObj->getChild("jupiter")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("jupiter")->setPosition(vec3(50, 40, 0));	//changing postiion
	tempObj->getChild("jupiter")->setRotation(vec3(50, 50, 60));	//change rotaion
	tempObj->getChild("jupiter")->setScale(vec3(0.45, 0.45, 0.45));	//change scele

	tempObj->addChild(new GameObject("saturn", tempObj, objects["teapot"], textures["saturn"], shaders["main"]));	//creating object
	tempObj->getChild("saturn")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("saturn")->setPosition(vec3(-65, 20, -65));	//changing postiion
	tempObj->getChild("saturn")->setRotation(vec3(0, -10, 70));	//change rotaion
	tempObj->getChild("saturn")->setScale(vec3(0.5, 0.5, 0.5));	//change scele

	tempObj->addChild(new GameObject("uranus", tempObj, objects["teapot"], textures["uranus"], shaders["main"]));	//creating object
	tempObj->getChild("uranus")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("uranus")->setPosition(vec3(-70, 30, 0));	//changing postiion
	tempObj->getChild("uranus")->setRotation(vec3(0, 30, 80));	//change rotaion
	tempObj->getChild("uranus")->setScale(vec3(0.3, 0.3, 0.3));	//change scele

	tempObj->addChild(new GameObject("neptune", tempObj, objects["teapot"], textures["neptune"], shaders["main"]));	//creating object
	tempObj->getChild("neptune")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("neptune")->setPosition(vec3(80, 50, 80));	//changing postiion
	tempObj->getChild("neptune")->setRotation(vec3(0, 60, 90));	//change rotaion
	tempObj->getChild("neptune")->setScale(vec3(0.3, 0.3, 0.3));	//change scele

	tempObj->addChild(new GameObject("pluto", tempObj, objects["teapot"], textures["pluto"], shaders["main"]));	//creating object
	tempObj->getChild("pluto")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("pluto")->setPosition(vec3(-90, 15, 0));	//changing postiion
	tempObj->getChild("pluto")->setRotation(vec3(0, -30, 100));	//change rotaion
	tempObj->getChild("pluto")->setScale(vec3(0.25, 0.25, 0.25));	//change scele


	//lander room node
	worldObject->getChild("room")->addChild(new GameObject("apolloRoomNode", worldObject->getChild("room")));	//creating node
	tempObj = worldObject->getChild("room")->getChild("apolloRoomNode"); //setting temp object for easy access
	tempObj->setActive(false);

	tempObj->addChild(new GameObject("lander", tempObj, objects["lander"], textures["lander"], shaders["main"]));	//creating object
	tempObj->getChild("lander")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("lander")->setPosition(vec3(0, -5, 0));	//changing postiion
	tempObj->getChild("lander")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("lander")->setScale(vec3(1, 1, 1));	//change scele

	//walker room node
	worldObject->getChild("room")->addChild(new GameObject("walkerNode", worldObject->getChild("room")));	//creating node
	tempObj = worldObject->getChild("room")->getChild("walkerNode"); //setting temp object for easy access
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

	worldObject->addChild(new GameObject("skybox", worldObject, objects["cubeMesh"], skyMaterial, shaders["sky"]));
	worldObject->getChild("skybox")->addComponent(RENDER_COMPONENT);
	worldObject->getChild("skybox")->setForceRender(true);
	worldObject->getChild("skybox")->setScale(vec3(20, 20, 20));	//change scele

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
	shaders["sky"]->cleanUp();
	objects["teapot"]->cleanUp();
	objects["cubeMesh"]->cleanUp();
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
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(true);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_2:
		cout << "set teapot room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(true);
		worldObject->getChild("room")->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_3:
		cout << "set old room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("apolloRoomNode")->setActive(true);
		worldObject->getChild("room")->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_4:
		cout << "set scifi room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("walkerNode")->setActive(true);
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
