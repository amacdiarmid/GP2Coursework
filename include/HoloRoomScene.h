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
private:

};

#endif