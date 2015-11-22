#ifndef _WINDOW_H
#define _WINDOW_H

#include "SDL2.h"
#include "OpenGL.h"
#include "Game.h"
#include "FileSystem.h"
#include "KeyboardListener.h"


extern  IkeyboardListener *keyboard; // this nees to be a vector

void createWindow(string gameName);
void destroyWindow();
void windowLoop();

#endif