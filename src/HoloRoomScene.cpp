#include "HoloRoomScene.h"
#include "Editor.h"
#include "OpenGL.h"

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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glUseProgram(shaders["textureSpecular"]->getShader());
	update();

	//Matrices
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &input->getMVPmatrix()[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniform3f(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "viewPos"), input->getWorldPoint().x, input->getWorldPoint().y, input->getWorldPoint().z);
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}

	//light properties
	glUniform3fv(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "light.position"),1, value_ptr(light.position));
	glUniform3fv(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "light.ambient"), 1, value_ptr(light.ambient) );
	glUniform3fv(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "light.diffuse"), 1, value_ptr(light.diffuse));
	glUniform3fv(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "light.specular"), 1, value_ptr(light.specular));


	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}

	//Material properties
	glUniform1f(glGetUniformLocation(shaders["textureSpecular"]->getShader(), "material.shininess"), material.shininess);
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}
	glUniform3fv(textureLocationSpecular, 1, value_ptr(material.specular));

	//Bind diffuse map
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, diffuseMap);



	//Bind specular map
	//glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, *textures["specularMap"]->getTexture());

	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &input->GetViewMatrix()[0][0]);

	//glUniformMatrix4fv(depthBiasLocation, 1, GL_FALSE, &depthBias[0][0]);
	//glUniform3f(lightLocation, lightInvDir.x, lightInvDir.y, lightInvDir.z);
	//glm::vec3 lightPos = glm::vec3(4, 4, 4);
	//glUniform3f(lightId, lightPos.x, lightPos.y, lightPos.z);
	/*glUniform1f(materialShininessLoc, materialShininess);
	glUniform3f(materialSPecularLoc, materialSpecularColor.x, materialSpecularColor.y, materialSpecularColor.z);
	glUniform3f(gLightPosLoc, gLight.position.x, gLight.position.y, gLight.position.z);
	glUniform3f(gLightIntensitiesLoc, gLight.intensities.x, gLight.intensities.y, gLight.intensities.z);
	glUniform1f(gLightAttenuationLoc, gLight.attenuation);
	glUniform1f(gLightAmbientCoeLoc, gLight.ambientCoefficient);
	glUniform3f(cameraPosLoc, input->getWorldPoint().x, input->getWorldPoint().y, input->getWorldPoint().z);*/

	//glActiveTexture(GL_TEXTURE0);

	//glUniform1i(textureSamplerLocation, 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, depthTexture);
	//glUniform1i(shadowMapLocation, 1);

	worldObject->render(fustrum);


	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in rendering scene " << err << endl;
	}

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

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in updating scene " << err << endl;
	}

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

	Object *tea = new Object();
	tea->createBuffer("/utah-teapot.fbx");

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
	textures.insert(pair<string, Texture*>("gray", new Texture("gray")));
	textures["gray"]->createTexture("/gray.png");
	//Diffuse map will be the normal texture for the model
	//Specular map will be used for specular highlights on the model
	//We seperate these so that if we have objects made of different materials,
	//they have different specular levels. 
	material.diffuseTexture = new Texture("diffuseMap");
	textures.insert(pair<string, Texture*>("diffuseMap", material.diffuseTexture));
	textures["diffuseMap"]->createTexture("/SunTexture.png"); //replace texture
	//material.specularTexture = new Texture("specularMap");
	//textures.insert(pair<string, Texture*>("specularMap", material.specularTexture));
	//textures["specularMap"]->createTexture("/SunTexture.png"); //replace texture


	//create shaders
	Shader * s = new Shader("main");
	s->attatchVertexShader("/textureVS.glsl");
	s->attatchFragmentShader("/textureFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("main", s));

	s = new Shader("textureSpecular");
	s->attatchVertexShader("/final Shaders/textureSpecularVS.glsl");
	s->attatchFragmentShader("/final Shaders/textureSpecularFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("textureSpecular", s));

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

	//add scene graph. this could be an external file or another function but it is here for now 

	loadScene(worldObject, name, this);

	//uncomment for world reset
	//worldObject->addChild(new GameObject("player", worldObject, input));
	//worldObject->getChild("player")->addComponent(INPUT_COMPONENT);

	//worldObject->addChild(new GameObject("sun", worldObject, objects["teapot"], textures["sun"], shaders["shadowMap"]));
	//worldObject->getChild("sun")->addComponent(RENDER_COMPONENT);

	//worldObject->getChild("sun")->addChild(new GameObject("earth", worldObject, objects["teapot"], textures["earth"], shaders["shadowMap"]));
	//worldObject->getChild("sun")->getChild("earth")->addComponent(RENDER_COMPONENT);
	//worldObject->getChild("sun")->getChild("earth")->changePosition(vec3(0, 10, 20));

	//worldObject->getChild("sun")->getChild("earth")->addChild(new GameObject("moon", worldObject, objects["teapot"], textures["moon"], shaders["shadowMap"]));
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

	depthMVPLocation = glGetUniformLocation(shaders["firstPassDepth"]->getShader(), "depthMVP");

	//ShadowFramebuffer();
	//BuildQuad();
	//materialShininess = 100;
	//gLight.position = glm::vec3(10, 30, 10);
	//gLight.intensities = glm::vec3(0.2, 0, 0); //white
	//gLight.attenuation = 0.2f;
	//gLight.ambientCoefficient = 0.605f;



	GLuint currentShader = shaders["textureSpecular"]->getShader();

	//textureSamplerLocation = glGetUniformLocation(currentShader, "texture0");
	MVPLocation = glGetUniformLocation(currentShader, "MVP");
	//materialShininessLoc = glGetUniformLocation(currentShader, "materialShininess");
	//materialSPecularLoc = glGetUniformLocation(currentShader, "materialSpecularColor");
	//gLightPosLoc = glGetUniformLocation(currentShader, "light.position");
	//gLightIntensitiesLoc = glGetUniformLocation(currentShader, "light.intensities");
	//gLightAttenuationLoc = glGetUniformLocation(currentShader, "light.attenuation");
	//gLightAmbientCoeLoc = glGetUniformLocation(currentShader, "light.ambientCoefficient");
	//cameraPosLoc = glGetUniformLocation(currentShader, "cameraPosition");
	////viewLocation = glGetUniformLocation(currentShader, "V");
	modelLocation = glGetUniformLocation(currentShader, "model");
	////depthBiasLocation = glGetUniformLocation(currentShader, "DepthBiasMVP");
	////shadowMapLocation = glGetUniformLocation(currentShader, "shadowMap");
	////lightLocation = glGetUniformLocation(currentShader, "LightInvDirection");
	////lightId = glGetUniformLocation(currentShader, "LightPosition_worldspace");
	textureLocationDiffuse = glGetUniformLocation(currentShader, "material.diffuse");
	textureLocationSpecular = glGetUniformLocation(currentShader, "material.specular");
	


	light.position = vec3(0.0f,-10, 22.0f);
	light.ambient = vec3(0.1f, 0.1f, 0.1f);
	light.diffuse = vec3(0.9f, 0.9f, 0.9f);
	light.specular = vec3(0.5f, 1.0f, 1.0f);
	

	material.shininess = 100000;
	material.specular = vec3(1.0f, 1.0f, 1.0f);

	glUseProgram(shaders["textureSpecular"]->getShader());
	glUniform1i(textureLocationSpecular, 1);
	glUniform1i(textureLocationDiffuse, 0);

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