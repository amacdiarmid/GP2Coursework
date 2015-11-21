#ifndef _SAVINGDATA_H
#define _SAVINGDATA_H


#define XMLCheckResult(a_eResult) if(a_eResult !=XML_SUCCESS) { cout << "Error: " <<a_eResult <<endl; }

#include "Common.h"
#include "tinyxml2.h"
#include "GameObject.h"

using namespace tinyxml2;

void saveScene(GameObject* worldObject, string tempName);
void saveObject(GameObject* tempObject, XMLElement* parentNode);
void loadScene();

#endif