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
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	GLenum err = GL_NO_ERROR;
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

	mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);

	depthBias = biasMatrix * depthMVP;

}


void HoloRoomScene::createScene()
{
	//CreateFrameBuffer(); ENable for post processing
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	editor = new Editor(this);
	debugMode = false;

	input = new PlayerController();
	Object *tea = new Object();
	tea->createBuffer("/utah-teapot.fbx");


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
	objects.insert(pair<string, Object*>("lander", new Object("lander")));
	objects["lander"]->createBuffer("/lander.FBX");
	
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.FBX");

	objects.insert(pair<string, Object*>("teapotRoom", new Object("teapotRoom")));
	objects["teapotRoom"]->createBuffer("/TheTeapotRoom.FBX");
	objects.insert(pair<string, Object*>("walkerRoom", new Object("walkerRoom")));
	objects["walkerRoom"]->createBuffer("/TheWalkerRoom.FBX");
	
	objects.insert(pair<string, Object*>("cubeMesh", new Cube("cubeMesh")));
	objects["cubeMesh"]->createBuffer();

	//create textures
	textures.insert(pair<string, Texture*>("sun", new Texture("sun")));
	textures["sun"]->createTexture("/SunTexture.png");

	textures.insert(pair<string, Texture*>("lander", new Texture("lander")));
	textures["lander"]->createTexture("/apollo map.jpg");

	textures.insert(pair<string, Texture*>("teapotRoom", new Texture("teapotRoom")));
	textures["teapotRoom"]->createTexture("/teapotRoom.jpg");
	textures.insert(pair<string, Texture*>("walkerRoom", new Texture("walkerRoom")));
	textures["walkerRoom"]->createTexture("/walkerRoom.jpg");

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

	//teapot room node done
	worldObject->addChild(new GameObject("teapotRoomNode", worldObject));	//creating node
	tempObj = worldObject->getChild("teapotRoomNode"); //setting temp object for easy access
	tempObj->setPosition(vec3(0, 0, 0));
	tempObj->setActive(true);
	
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

	tempObj->addChild(new GameObject("walkerRoom", tempObj, objects["walkerRoom"], textures["walkerRoom"], shaders["main"]));	//creating object
	tempObj->getChild("walkerRoom")->addComponent(RENDER_COMPONENT);	//adding render comp
	tempObj->getChild("walkerRoom")->setPosition(vec3(0, -25, 0));	//changing postiion
	tempObj->getChild("walkerRoom")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("walkerRoom")->setScale(vec3(3, 3, 3));	//change scele
	
	//set skybox
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
	shaders["sky"]->cleanUp();
	shaders["shadowMap"]->cleanUp();	
	objects["teapot"]->cleanUp();
	objects["cubeMesh"]->cleanUp();
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
	//cout << "Key down " << key << endl;
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
		cout << "set teapot room" << endl;
		worldObject->getChild("teapotRoomNode")->setActive(true);
		worldObject->getChild("apolloRoomNode")->setActive(false);
		worldObject->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_2:
		cout << "set apollo room" << endl;
		worldObject->getChild("teapotRoomNode")->setActive(false);
		worldObject->getChild("apolloRoomNode")->setActive(true);
		worldObject->getChild("walkerNode")->setActive(false);
		break;
	case SDLK_3:
		cout << "set walker room" << endl;
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
	//cout << "Key up " << key << endl;
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