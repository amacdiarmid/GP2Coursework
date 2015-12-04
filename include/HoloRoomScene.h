#ifndef _HOLOROOMSCENE_H
#define _HOLOROOMSCENE_H

#include "Scene.h"

class HoloRoomScene : public IkeyboardListener, public Scene 
{
public:
	HoloRoomScene();
	HoloRoomScene(string name);
	~HoloRoomScene();

	void update() override;
	void render() override;
	void createScene() override;
	void destroyScene() override;
	void SceneLoop() override;

	//debug stuff
	GameObject *getGameObject(string command) override;
	GameObject *getWorldObject() override;
	Object *getObject(string command) override;
	Texture *getTexture(string command) override;
	Shader *getShader(string command) override;
	string getName() override;

	void onKeyDown(SDL_Keycode key) override;
	void onkeyUp(SDL_Keycode key) override;

	//ShadowMapping
	void ShadowFramebuffer();
	void BuildQuad();
	void ShadowMapPass();
	void UpdateLightPerspMVP();
	void RenderQuad();

	//Post Processing
	void CreateFrameBuffer();
	void CleanUpFrameBuffer();
	void RenderPostQuad();

private:
	//ShadowMapping 1st pass
	GLuint depthTexture;
	GLuint depthMVPLocation;
	GLuint shadowFBO;
	mat4 depthMVP;
	GLuint quadTexture;
	GLuint quadVBO;
	//ShadowMapping 2nd pass
	Shader *shadowMapProgram;
	GLuint textureSamplerLocation;
	GLuint MVPLocation;
	GLuint viewLocation;
	GLuint modelLocation;
	GLuint depthBiasLocation;
	GLuint shadowMapLocation;
	GLuint lightLocation;
	vec3 lightInvDir = glm::vec3(0.5, 2, 2);
	mat4 depthBias;
	glm::mat4 ModelMatrix = glm::mat4(1.0);

	//PostProcessing
	GLuint FBOTexture;
	const int FRAME_BUFFER_WIDTH = 640;
	const int FRAME_BUFFER_HEIGHT = 480;
	GLuint FBODepthBuffer;
	GLuint frameBufferObject;
	GLuint fullScreenVAO;
	GLuint fullScreenVBO;
	GLuint fullScreenShaderProgram;
	unsigned int lastTicks, currentTicks;
	float elapsedTime;
	float totalTime;
	vec2 screenResolution = vec2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
};

#endif