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
	curMesh = NULL;
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
		else if (com == "transform")
		{
			if (curGameObject == NULL)
			{
				cout << "no object" << endl;
			}
			else
			{
				cout << "curent pos " << curGameObject->getPosition().x << " " << curGameObject->getPosition().z << endl;
				do
				{
					cout << "adjust transform" << endl;
					cin >> com;
					if (com == "setPos")
					{
						setPos();
					}
					else if (com == "movePos")
					{
						movePos();
					}
				} while (com != "doneTransform");
			}
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
	cout << "game object assigned " << curGameObject->getName() << endl;
}

void Editor::assignObject()
{
	cout << "get mesh name" << endl;
	string com;
	cin >> com;
	curMesh = curScene->getObject(com);
	cout << "mesh assigned " << curName << endl;
}

void Editor::assignTexture()
{
	cout << "get texture name" << endl;
	string com;
	cin >> com;
	curTexture = curScene->getTexture(com);
	cout << "texture assigned " << curTexture->getName() << endl;
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
	if (curName != "" && curGameObject != NULL && curMesh != NULL && curTexture != NULL && curShader != NULL)
	{
		cout << "spawning object" << endl;
		curGameObject->addChild(new GameObject(curName, curGameObject, curMesh, curTexture->getTexture(), curShader));
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
		if (curMesh == NULL)
		{
			cout << "no object" << endl;
		}
		else
		{
			cout << "cur object " << curMesh->getName() << endl;
		}
		if (curTexture == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur texture " << curTexture->getName() << endl;
		}
		if (curShader == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur Shader " << curShader->getName() << endl;
		}
	}
}

void Editor::setPos()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		int xCoord;
		cout << "set X" << endl;
		cin >> xCoord;
		
		int yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		int zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->setPosition(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}
}

void Editor::movePos()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		int xCoord;
		cout << "set X" << endl;
		cin >> xCoord;

		int yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		int zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->changePosition(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}

}