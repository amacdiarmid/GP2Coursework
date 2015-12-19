#include "HoloRoomScene.h"
#include "Editor.h"


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
	glClearColor(0.0f, 0.0f, 0.5f, 0.5f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1024, 768);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//backface culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	glUseProgram(shaders["shadowMap"]->getShader());
	update();

	materialShininess++;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &input->getMVPmatrix()[0][0]);
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &input->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	//glUniformMatrix4fv(depthBiasLocation, 1, GL_FALSE, &depthBias[0][0]);
	//glUniform3f(lightLocation, lightInvDir.x, lightInvDir.y, lightInvDir.z);
	//glm::vec3 lightPos = glm::vec3(4, 4, 4);
	//glUniform3f(lightId, lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(materialShininessLoc, materialShininess);
	glUniform3f(materialSPecularLoc, materialSpecularColor.x, materialSpecularColor.y, materialSpecularColor.z);
	glUniform3f(gLightPosLoc, gLight.position.x, gLight.position.y, gLight.position.z);
	glUniform3f(gLightIntensitiesLoc, gLight.intensities.x, gLight.intensities.y, gLight.intensities.z);
	glUniform1f(gLightAttenuationLoc, gLight.attenuation);
	glUniform1f(gLightAmbientCoeLoc, gLight.ambientCoefficient);
	glUniform3f(cameraPosLoc, input->getWorldPoint().x, input->getWorldPoint().y, input->getWorldPoint().z);

	glActiveTexture(GL_TEXTURE0);

	glUniform1i(textureSamplerLocation, 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, depthTexture);
	//glUniform1i(shadowMapLocation, 1);

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
	GLenum err = GL_NO_ERROR;
	input->Update();

	//i ++;
	//worldObject->getChild("sun")->setRotation(vec3(0, i, 0));
	//worldObject->getChild("sun")->getChild("earth")->setRotation(vec3(0, i, 0));
	//worldObject->getChild("sun")->getChild("earth")->getChild("moon")->changePosition(vec3(0.0f, 0.0f, -0.01f));

	worldObject->update(input->getMVPmatrix());

<<<<<<< HEAD
	/*
	GLenum err = GL_NO_ERROR;
=======
>>>>>>> origin/master
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in updating scene " << err << endl;
	}
<<<<<<< HEAD
	*/
=======

	mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);

	depthBias = biasMatrix * depthMVP;

>>>>>>> origin/master
}


void HoloRoomScene::createScene()
{
	//CreateFrameBuffer(); ENable for post processing
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	editor = new Editor(this);
	debugMode = false;

<<<<<<< HEAD
	//set this stuff up into object files 
=======
	Object *tea = new Object();
	tea->createBuffer("/utah-teapot.fbx");
>>>>>>> origin/master

	//create objects
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.fbx");
	objects.insert(pair<string, Object*>("holoRoom", new Object("holoRoom")));
	objects["holoRoom"]->createBuffer("/Holodome2.FBX");
	objects.insert(pair<string, Object*>("Dubstep", new Object("Dubstep")));
	objects["Dubstep"]->createBuffer("/[Dubstep]GUN.FBX");
	objects.insert(pair<string, Object*>("compCube", new Object("compCube")));
	objects["compCube"]->createBuffer("/2-foot Weighted Companion Cube autodesk.FBX");

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
<<<<<<< HEAD
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

	textures.insert(pair<string, Texture*>("Dubstep", new Texture("Dubstep")));
	textures["Dubstep"]->createTexture("/[Dubstep]GUN_Diffuse.png");
	textures.insert(pair<string, Texture*>("compCube", new Texture("compCube")));
	textures["compCube"]->createTexture("/companionCube.png");
=======
	textures.insert(pair<string, Texture*>("gray", new Texture("gray")));
	textures["gray"]->createTexture("/gray.png");
>>>>>>> origin/master

	//create shaders
	Shader * s = new Shader("main");
	s->attatchVertexShader("/textureVS.glsl");
	s->attatchFragmentShader("/textureFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("main", s));
	
	//Shadow Shaders
	s = new Shader("firstPassDepth");
	s->attatchVertexShader("/DepthVS.glsl");
	s->attatchFragmentShader("/DepthFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("firstPassDepth", s));

	s = new Shader("quadShader");
	s->attatchVertexShader("/quadVS.glsl");
	s->attatchFragmentShader("/quadFS.txt");
	s->createShader();
	shaders.insert(pair<string, Shader*>("quadShader", s));

	s = new Shader("shadowMap");
	s->attatchVertexShader("/shadowMapVS.glsl");
	s->attatchFragmentShader("/shadowMapFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("shadowMap", s));

	/*s = new Shader("textureShadow");
	s->attatchVertexShader("/textureShadowVS.glsl");
	s->attatchFragmentShader("/shadowMapFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("textureShadow", s));*/


	//create player/debug cam
	input = new PlayerController();
	fustrum = new Fustrum(input);
	fustrum->setUpCamera();
	fustrum->updateCamera();
	worldObject->setScene(this);

	//loadScene(worldObject, name, this);

	//uncomment for world reset
<<<<<<< HEAD
	GameObject *tempObj;

	//player
	worldObject->addChild(new GameObject("player", worldObject, input));
	worldObject->getChild("player")->addComponent(INPUT_COMPONENT);

	//skybox
	//david do stuff here

	//main room
	worldObject->addChild(new GameObject("room", worldObject, objects["holoRoom"], textures["wall"], shaders["main"]));	//creating object
	worldObject->getChild("room")->addComponent(RENDER_COMPONENT);	//adding render comp
	worldObject->getChild("room")->changePosition(vec3(0, -25, 0));	//changing position

	//empty room node
	worldObject->getChild("room")->addChild(new GameObject("emptyRoomNode", worldObject->getChild("room")));	//creating node
	worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(true);

	//teapot room node
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


	//old room node
	worldObject->getChild("room")->addChild(new GameObject("oldRoomNode", worldObject->getChild("room")));	//creating node
	tempObj = worldObject->getChild("room")->getChild("oldRoomNode"); //setting temp object for easy access
	tempObj->setActive(false);

	//scifi room node
	worldObject->getChild("room")->addChild(new GameObject("sciFiRoomNode", worldObject->getChild("room")));	//creating node
	tempObj = worldObject->getChild("room")->getChild("sciFiRoomNode"); //setting temp object for easy access
	tempObj->setActive(false);

	tempObj->addChild(new GameObject("Dubstep", tempObj, objects["Dubstep"], textures["Dubstep"], shaders["main"]));	//creating object
	tempObj->getChild("Dubstep")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("Dubstep")->setPosition(vec3(0, 0, 0));	//changing postiion
	tempObj->getChild("Dubstep")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("Dubstep")->setScale(vec3(0.25, 0.25, 0.25));	//change scele

	tempObj->addChild(new GameObject("compCube", tempObj, objects["compCube"], textures["compCube"], shaders["main"]));	//creating object
	tempObj->getChild("compCube")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("compCube")->setPosition(vec3(-50, 0, -50));	//changing postiion
	tempObj->getChild("compCube")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("compCube")->setScale(vec3(1, 1, 1));	//change scele
=======
	//worldObject->addChild(new GameObject("player", worldObject, input));
	//worldObject->getChild("player")->addComponent(INPUT_COMPONENT);

	//worldObject->addChild(new GameObject("sun", worldObject, objects["teapot"], textures["sun"], shaders["shadowMap"]));
	//worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	//worldObject->getChild("sun")->addChild(new GameObject("earth", worldObject, objects["teapot"], textures["earth"], shaders["shadowMap"]));
	//worldObject->getChild("sun")->getChild("earth")->addComponent(RENDER_COMPONENT);
	//worldObject->getChild("sun")->getChild("earth")->changePosition(vec3(0, 10, 20));

	//worldObject->getChild("sun")->getChild("earth")->addChild(new GameObject("moon", worldObject, objects["teapot"], textures["moon"], shaders["shadowMap"]));
	//worldObject->getChild("sun")->getChild("earth")->getChild("moon")->addComponent(RENDER_COMPONENT);
>>>>>>> origin/master

	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->printComponents();
	worldObject->printChildern();

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating scene " << err << endl;
	}

	depthMVPLocation = glGetUniformLocation(shaders["firstPassDepth"]->getShader(), "depthMVP");

	//ShadowFramebuffer();
	//BuildQuad();
	materialShininess = 100;
	gLight.position = glm::vec3(10, 30, 10);
	gLight.intensities = glm::vec3(0.2, 0, 0); //white
	gLight.attenuation = 0.2f;
	gLight.ambientCoefficient = 0.605f;

	GLuint currentShader = shaders["shadowMap"]->getShader();

	textureSamplerLocation = glGetUniformLocation(currentShader, "texture0");
	MVPLocation = glGetUniformLocation(currentShader, "MVP");
	materialShininessLoc = glGetUniformLocation(currentShader, "materialShininess");
	materialSPecularLoc = glGetUniformLocation(currentShader, "materialSpecularColor");
	gLightPosLoc = glGetUniformLocation(currentShader, "light.position");
	gLightIntensitiesLoc = glGetUniformLocation(currentShader, "light.intensities");
	gLightAttenuationLoc = glGetUniformLocation(currentShader, "light.attenuation");
	gLightAmbientCoeLoc = glGetUniformLocation(currentShader, "light.ambientCoefficient");
	cameraPosLoc = glGetUniformLocation(currentShader, "cameraPosition");
	//viewLocation = glGetUniformLocation(currentShader, "V");
	modelLocation = glGetUniformLocation(currentShader, "M");
	//depthBiasLocation = glGetUniformLocation(currentShader, "DepthBiasMVP");
	//shadowMapLocation = glGetUniformLocation(currentShader, "shadowMap");
	//lightLocation = glGetUniformLocation(currentShader, "LightInvDirection");
	//lightId = glGetUniformLocation(currentShader, "LightPosition_worldspace");
	
}

void HoloRoomScene::ShadowFramebuffer()
{
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.
	glReadBuffer(GL_NONE);

}

void HoloRoomScene::BuildQuad()
{
	const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	quadTexture = glGetUniformLocation(shaders["quadShader"]->getShader(), "texture");
}

void HoloRoomScene::ShadowMapPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glViewport(0, 0, 1024, 1024);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaders["firstPassDepth"]->getShader());

	UpdateLightPerspMVP();

	glUniformMatrix4fv(depthMVPLocation, 1, GL_FALSE, &depthMVP[0][0]);

	worldObject->render(fustrum);
}

void HoloRoomScene::UpdateLightPerspMVP()
{
	// Compute the MVP matrix from the light's point of view
	mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mat4 depthModelMatrix = glm::mat4(1.0);
	depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

}

void HoloRoomScene::RenderQuad()
{
	glViewport(0, 0, 512, 512);

	// Use our shader
	glUseProgram(shaders["quadShader"]->getShader());

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	// Set our "renderedTexture" sampler to user Texture Unit 0
	glUniform1i(quadTexture, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDisableVertexAttribArray(0);

}

void HoloRoomScene::destroyScene()
{
	shaders["main"]->cleanUp();
	shaders["shadowMap"]->cleanUp();	
	objects["teapot"]->cleanUp();
}

void HoloRoomScene::SceneLoop()
{
	windowLoop();
	//ShadowMapPass();
	render();
	//RenderQuad();
	//RenderPostQuad();
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
		worldObject->getChild("room")->getChild("oldRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("sciFiRoomNode")->setActive(false);
		break;
	case SDLK_2:
		cout << "set teapot room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(true);
		worldObject->getChild("room")->getChild("oldRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("sciFiRoomNode")->setActive(false);
		break;
	case SDLK_3:
		cout << "set old room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("oldRoomNode")->setActive(true);
		worldObject->getChild("room")->getChild("sciFiRoomNode")->setActive(false);
		break;
	case SDLK_4:
		cout << "set scifi room" << endl;
		worldObject->getChild("room")->getChild("emptyRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("oldRoomNode")->setActive(false);
		worldObject->getChild("room")->getChild("sciFiRoomNode")->setActive(true);
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

void HoloRoomScene::CreateFrameBuffer()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &FBOTexture);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, NULL);


	glGenRenderbuffers(1, &FBODepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, FBODepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, FBODepthBuffer);

	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		cout << "Issue with Framebuffers" << endl;
	}
	float vertices[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,

	};

	glGenVertexArrays(1, &fullScreenVAO);
	glBindVertexArray(fullScreenVAO);

	glGenBuffers(1, &fullScreenVBO);
	glBindBuffer(GL_ARRAY_BUFFER, fullScreenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,  // attribute
		2,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/simplePostProcessVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/simplePostProcessFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	fullScreenShaderProgram = glCreateProgram();
	glAttachShader(fullScreenShaderProgram, vertexShaderProgram);
	glAttachShader(fullScreenShaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(fullScreenShaderProgram, 0, "vertexPosition");

	glLinkProgram(fullScreenShaderProgram);
	checkForLinkErrors(fullScreenShaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

void HoloRoomScene::CleanUpFrameBuffer()
{
	glDeleteProgram(fullScreenShaderProgram);
	glDeleteBuffers(1, &fullScreenVBO);
	glDeleteVertexArrays(1, &fullScreenVAO);
	glDeleteFramebuffers(1, &frameBufferObject);
	glDeleteRenderbuffers(1, &FBODepthBuffer);
	glDeleteTextures(1, &FBOTexture);
}

void HoloRoomScene::RenderPostQuad()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(fullScreenShaderProgram);

	GLint textureLocation = glGetUniformLocation(fullScreenShaderProgram, "texture0");
	GLint timeLocation = glGetUniformLocation(fullScreenShaderProgram, "time");
	GLint resolutionLocation = glGetUniformLocation(fullScreenShaderProgram, "resolution");

	glUniform1f(timeLocation, totalTime);
	glUniform2fv(resolutionLocation, 1, value_ptr(screenResolution));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);
	glUniform1i(textureLocation, 0);

	glBindVertexArray(fullScreenVAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}