#include "Editor.h"
#include "Scene.h"

Editor::Editor()
{

}

Editor::Editor(Scene *tempScene)
{
	curScene = tempScene;
	curName = "";
	curGameObject = NULL;
	curObject = NULL;
	curTexture = NULL;
	curShader = NULL;
}

Editor::~Editor()
{

}

void Editor::readCommand()
{
	string com;
	do
	{
		cout << "insert command" << endl;
		cin >> com;
		if (com == "assignObjectName")
		{
			assignName();
		}
		else if (com == "assignGameObject")
		{
			assignGameObject();
		}
		else if (com == "assignMesh")
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
	} while (com != "done");
}

void Editor::assignName()
{
	cout << "assign name" << endl;
	string com;
	cin >> com;
	curName = com;
	cout << "name assigned " << curName << endl;
}

void Editor::assignGameObject()
{
	cout << "get gameObject name" << endl;
	string com;
	cin >> com;
	curGameObject = curScene->getGameObject(com);
	cout << "game object assigned " << curName << endl;
}

void Editor::assignObject()
{
	cout << "get mesh name" << endl;
	string com;
	cin >> com;
	curObject = curScene->getObject(com);
	cout << "mesh assigned " << curName << endl;
}

void Editor::assignTexture()
{
	cout << "get texture name" << endl;
	string com;
	cin >> com;
	curTexture = curScene->getTexture(com)->getTexture();
	cout << "texture assigned " << curName << endl;
}

void Editor::assignShader()
{
	cout << "get shader name" << endl;
	string com;
	cin >> com;
	curShader = curScene->getShader(com);
	cout << "shader assigned " << curName << endl;
}

void Editor::spawnObject()
{
	if (curName != "" && curGameObject != NULL && curObject != NULL && curTexture != NULL && curShader != NULL)
	{
		cout << "spawning object" << endl;
		curGameObject->addChild(new GameObject(curName, curGameObject, curObject, curTexture, curShader));
	}
	else
	{
		if (curName == "")
		{
			cout << "no name" << endl;
		}
		else
		{
			cout << "cur name: " << curName << endl;
		}
		if (curGameObject == NULL)
		{
			cout << "no Game object" << endl;
		}
		else
		{
			cout << "cur Game Object " << curGameObject->getName() << endl;
		}
		if (curObject == NULL)
		{
			cout << "no object" << endl;
		}
		else
		{
			cout << "cur object " << curObject << endl;
		}
		if (curTexture == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur texture " << curTexture << endl;
		}
		if (curShader == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur Shader " << curShader << endl;
		}
	}
}