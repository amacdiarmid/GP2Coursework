#include "Editor.h"
#include "Scene.h"

Editor::Editor()
{

}

Editor::Editor(Scene *tempScene)
{
	curScene = tempScene;
}

Editor::~Editor()
{

}

void Editor::readCommand()
{
	cout << "insert command" << endl;
	string com;
	cin >> com;
	if (com == "assignObjectName")
	{
		assignName();
	}
	else if (com == "assignGameObject")
	{
		assignGameObject();
	}
	else if (com == "assignObject")
	{
		assignObject();
	}
	else if (com == "assignTexture")
	{
		assignTexture();
	}
	else if (com == "assignShader")
	{
		assignShader();
	}
	else if (com == "spawnObject")
	{
		spawnObject();
	}
	else
	{
		cout << "unknown command" << endl;
	}
}

void Editor::assignName()
{
	cout << "game object name" << endl;
	string com;
	cin >> com;
	curName = com;
}

void Editor::assignGameObject()
{
	cout << "get gameObject name" << endl;
	string com;
	cin >> com;
	curScene->getGameObject(com);
}

void Editor::assignObject()
{
	cout << "get object name" << endl;
	string com;
	cin >> com;
	curScene->getObject(com);

}

void Editor::assignTexture()
{
	cout << "get texture name" << endl;
	string com;
	cin >> com;
	curScene->getTexture(com);

}

void Editor::assignShader()
{
	cout << "get shader name" << endl;
	string com;
	cin >> com;
	curScene->getShader(com);

}

void Editor::spawnObject()
{
	cout << "spawning object" << endl;
	curGameObject->addChild(new GameObject(curName, curGameObject, curObject, curTexture, curShader));
}