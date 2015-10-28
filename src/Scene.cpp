#include "Scene.h"
#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

Vertex verts[] = {
	//front
	{ vec3(-0.5f, 0.5f, 0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f),
	vec2(0.0f, 0.0f) }, //top left
	{ vec3(-0.5f, -0.5f, 0.5f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f),
	vec2(0.0f, 1.0f) }, //bottom left
	{ vec3(0.5f, -0.5f, 0.5f),
	vec4(0.0f, 1.0f, 1.0f, 1.0f),
	vec2(1.0f, 1.0f) }, //bottom right
	{ vec3(0.5f, 0.5f, 0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f),
	vec2(1.0f, 0.0f) }, //top right
	//back
	{ vec3(-0.5f, 0.5f, -0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f),
	vec2(0.0f, 0.0f) }, //top left 
	{ vec3(-0.5f, -0.5f, -0.5f),
	vec4(1.0f, 1.0f, 0.0f, 1.0f),
	vec2(0.0f, 1.0f) }, //bottom left 
	{ vec3(0.5f, -0.5f, -0.5f),
	vec4(0.0f, 0.5f, 0.5f, 0.5f),
	vec2(1.0f, 1.0f) }, //bottom right
	{ vec3(0.5f, 0.5f, -0.5f),
	vec4(1.0f, 0.0f, 1.0f, 1.0f),
	vec2(1.0f, 0.0f) }, //top right 
};

GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,
	//left
	4, 5, 1,
	4, 1, 0,
	//right
	3, 7, 2,
	7, 6, 2,
	//bottom
	1, 5, 2,
	6, 2, 5,
	//top
	4, 0, 7,
	0, 7, 3,
	//back
	4, 5, 6,
	4, 7, 6,
};

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLuint shaderProgram = 0;
GLuint textureMap;
GLuint fontTexture;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;

//move object
vec3 movementVec = vec3(0.0f, 0.0f, 0.0f);
//move camera 
vec3 worldPoint = vec3(0.0f, 0.0f, 10.0f);
vec3 lookAtPoint = vec3(0.0f, 0.0f, 0.0f);

void render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(shaderProgram);

	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));

	//get the uniform for the movementVec
	GLint moveVecLocation = glGetUniformLocation(shaderProgram, "movementVec");
	glUniform3fv(moveVecLocation, 1, value_ptr(movementVec));

	//get the uniform for the texture coords
	GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glUniform1i(texture0Location, 0);

	glBindVertexArray(VAO);
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

}

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	viewMatrix = lookAt(worldPoint, lookAtPoint, vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	MVPMatrix = projMatrix*viewMatrix*worldMatrix;
}


Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::createScene()
{
	//load texture & bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/Texture.png";
	textureMap = loadTextureFromFile(texturePath);

	glBindTexture(GL_TEXTURE_2D, textureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	//load font and bind 
	string fontPath = ASSET_PATH + FONT_PATH + "/OratorStd.otf";
	fontTexture = loadTextureFromFont(fontPath, 18, "test");

	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//gen vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create vertex buffer object
	glGenBuffers(1, &VBO);
	//make the VBO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	//create element buffer object 
	glGenBuffers(1, &EBO);
	//make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//copy the index date to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tell the shader that 0 is the position element 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	//send the colour to the shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	//send the text coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//link attributes 
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
	//now we can delete the VS and FS programs 
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);


}

void Scene::destroyScene()
{
	glDeleteTextures(1, &textureMap);
	glDeleteTextures(1, &fontTexture);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Scene::SceneLoop()
{
	update();
	render();
}