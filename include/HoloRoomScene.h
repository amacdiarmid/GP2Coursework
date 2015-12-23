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
	void mouseMove(SDL_MouseMotionEvent motion) override;
private:

	//float specularPower = 5.0f;
	//float lightDirection[3] = float[](0.0, 0.0, 1.0f);
	//vec4 diffMatColour = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	//vec4 specMatColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

#endif