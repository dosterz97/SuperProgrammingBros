#include "stdafx.h"
#include "SDL.h"
#include "include\StateManager.h"
#include <iostream>

using namespace std;

StateManager::StateManager(SDL_Window* window, SDL_Surface* screen) 
{
	this->window = window;
	this->screen = screen;
}

StateManager::~StateManager()
{
}


//handle the SDL events given by SDL_PollEvent
//Precondition: SDL_Window* and SDL_Surface*
void StateManager::handleEvents() {
	bool exit = false;

	Uint32 backgroundColor = SDL_MapRGB(screen->format, 0, 0, 0);

	SDL_Event SDLEvent;
	//Game Loop
	while (!exit)
	{
		//Poll events
		while (SDL_PollEvent(&SDLEvent) != 0)
		{
			if (SDLEvent.type == SDL_QUIT)
				exit = true;
			if (SDLEvent.type == SDL_KEYDOWN) {
				switch (SDLEvent.key.keysym.sym) {
				case SDLK_UP: 
					cout << "hey hey" << endl;
					break;
				}
			}

		}

		SDL_FillRect(this->screen, NULL, backgroundColor);//Fill the background color

		SDL_UpdateWindowSurface(this->window);//Update Window
	}
}


//step all of the objects
void StateManager::stepAll() {
	for (int i = 0; i < this->objects.size(); i++) {
		if (this->objects.at(i) != NULL) {
			this->objects.at(i)->step();
		}
	}
	this->player.step();
}


//load the map based on the given numbers
//precondition: world (int), level (int)
void StateManager::loadMap(int world, int level) {
	
}


//draw all objects who have changes
void StateManager::draw() {

}