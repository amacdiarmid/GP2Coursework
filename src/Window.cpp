#include "Common.h"
#include "Window.h"

SDL_Window *window;
SDL_GLContext glContext;
IkeyboardListener *keyboard;

void createWindow()
{
	ChangeWorkingDirectory();

	initSDL2();
	initSDL2Image();
	initSDL2TTF();

	//ask for version 4.2 of openGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//create a window 
	window = SDL_CreateWindow("SDL", //window title
		SDL_WINDOWPOS_CENTERED, // x position centered
		SDL_WINDOWPOS_CENTERED, //y position centered
		640, //width in pixels 
		480, //height in pixels 
		SDL_WINDOW_OPENGL //flags
		);

	//create an openGL context associated with the window
	glContext = SDL_GL_CreateContext(window);

	//initalisation
	//call our initOpenGL function
	initOpenGL();
	//set our viewport
	setViewport(640, 480);

	createGame();
}

void destroyWindow()
{
	//clean up in reverse order
	//clean out the buffers 
	destroyGame();
	//destroy openGL
	SDL_GL_DeleteContext(glContext);
	//destroy window
	SDL_DestroyWindow(window);
	//destroy image Lib
	IMG_Quit();
	//destroy SDL font lib
	TTF_Quit();
	//destroy initalization 
	SDL_Quit();
}

bool windowLoop()
{
	//value to hold the event generated by SDL
	SDL_Event event;
	//while we still have events in the queue
	while (SDL_PollEvent(&event))
	{
		//get event type
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			//set our bool which controls the loop to false
			return false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			for each (auto var in keyboardListeners)
			{
				var->onKeyDown(event.key.keysym.sym);
			}
		//	switch (event.key.keysym.sym)
		//	{
		//	case SDLK_p:
		//		cout << "Debug Mode" << endl;
		//		break;
		//		/*
		//		if (debugMode)
		//		{
		//			cout << "debug mode off" << endl;
		//			debugMode = false;
		//		}
		//		else
		//		{
		//			cout << "debug mode on" << endl;
		//			debugMode = true;
		//		}*/
		//	case SDLK_l:
		//		cout << "read commands" << endl;
		//		break;
		//		//if (debugMode)
		//		//{
		//		//	editor->readCommand();
		//		//}
		//	default:
		//		break;
		}
	}

	gameLoop();

	//call swap so that our GL back buffer is displayed
	SDL_GL_SwapWindow(window);
}