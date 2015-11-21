#include "SavingData.h"

XMLDocument xmlDoc;

void saveScene(GameObject* worldObject, string TempName)
{
	XMLNode * pRoot = xmlDoc.NewElement("root");

	xmlDoc.InsertFirstChild(pRoot);

	XMLElement * worldElement = xmlDoc.NewElement("world object");

	saveObject(worldObject, worldElement);

	pRoot->InsertEndChild(worldElement);

	xmlDoc.InsertEndChild(pRoot);

	string filePath = ASSET_PATH + SCENE_PATH + "/" + TempName + ".banana";
	XMLError eResult = xmlDoc.SaveFile(filePath.c_str());
	XMLCheckResult(eResult);
}

void saveObject(GameObject* tempObject, XMLElement* parentNode)
{
	XMLElement * objectElement = xmlDoc.NewElement("object");

	XMLElement * nameElement = xmlDoc.NewElement("name");
	nameElement->SetText(tempObject->getName().c_str());
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("world");
	nameElement->SetText(tempObject->getActive());
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("active");
	nameElement->SetText(tempObject->getActive());
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("model");
	if (tempObject->getModel() != NULL)
	{
		nameElement->SetText(tempObject->getModel()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("texture");
	if (tempObject->getTexture() != NULL)
	{
		nameElement->SetText(tempObject->getTexture()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("shader");
	if (tempObject->getShader() != NULL)
	{
		nameElement->SetText(tempObject->getShader()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("worldPos");
	nameElement->SetAttribute("x", tempObject->getWorldPos().x);
	nameElement->SetAttribute("y", tempObject->getWorldPos().y);
	nameElement->SetAttribute("z", tempObject->getWorldPos().z);
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("localPos");
	nameElement->SetAttribute("x", tempObject->getLocalPos().x);
	nameElement->SetAttribute("y", tempObject->getLocalPos().y);
	nameElement->SetAttribute("z", tempObject->getLocalPos().z);
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("components");
	for (auto i = tempObject->getCompMap()->begin(); i != tempObject->getCompMap()->end(); i++)
	{
		XMLElement * loopElement = xmlDoc.NewElement("component");
		loopElement->SetText(i->first);
		nameElement->InsertEndChild(loopElement);
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = xmlDoc.NewElement("children");
	for (auto i = tempObject->getChildrenMap()->begin(); i != tempObject->getChildrenMap()->end(); i++)
	{
		XMLElement * loopElement = xmlDoc.NewElement("child");
		saveObject(i->second, nameElement);
		nameElement->InsertEndChild(loopElement);
	}
	objectElement->InsertEndChild(nameElement);

	parentNode->InsertEndChild(objectElement);
}

void loadScene()
{

}