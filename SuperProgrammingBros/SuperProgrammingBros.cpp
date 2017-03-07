// SuperProgrammingBros.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDL.h"
#include <iostream>
#include "include\StateManager.h"

using namespace std;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

bool initialize();
void close();

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
	if (!initialize())
	{
		cout << "Could not initialize" << endl;
		return -1;
	}

	StateManager* sm = new StateManager(window, screen);

	sm->handleEvents();
	
	return 0;
}


bool initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initalized: SDL Error %s\n" << SDL_GetError() << endl;
		return false;
	}

	window = SDL_CreateWindow("SUPER PROGRAMMING BROS",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		cout << "Window could not be created. SDL_Error: %s\n" << SDL_GetError() << endl;
		return false;
	}

	screen = SDL_GetWindowSurface(window);
	return true;
}


//Close up the window
void close()
{
	//Clean up window
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();//Quit all of SDL
}