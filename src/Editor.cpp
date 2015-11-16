#include "Editor.h"

Scene *curScene;
string curName;
GameObject *curGameObject;
Object *curObject;
GLuint *curTexture;
Shader *curShader;

void readCommand()
{
	string com;
	cin >> com;
	if (com == "spawn")
	{
		cout << "command: Spawn" << endl;
		cout << "set name" << endl;
		string name;
		cout << "set gameObject" << endl;
		string gameObject;
		cout << "set object" << endl;
		string object;
		cout << "set texture" << endl;
		string texture;
		cout << "set shader" << endl;
		string shader;
	}
	else
	{
		cout << "unknown command" << endl;
	}
}

void assignGameObject()
{

}

void assignObject()
{

}

void assignTexture()
{

}

void assignShader()
{

}

void spawnObject()
{
	curGameObject->addChild(new GameObject(curName, curGameObject, curObject, curTexture, curShader));
}