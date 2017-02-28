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
void StateManager::handleEvents() 
{
	bool exit = false;

	double t = 0.0;
	double dt = 0.01;

	double currentTime = 0;
	double accumulator = 0.0;


	Uint32 backgroundColor = SDL_MapRGB(screen->format, 0, 0, 0);
	Animation myAnimation("mario-small", true);
	player.setAnimation(myAnimation);
	int frame = 0;
	int animation = 1;

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
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_UP:
					cout << "hey up" << endl;
					player.setVY(-2);
					cout << player.getVY() << endl;
					break;
				case SDLK_RIGHT:
					cout << "hey right" << endl;
					player.setVX(2);
					cout << player.getVX() << endl;
					break;
				case SDLK_DOWN:
					cout << "hey down" << endl;
					player.setVY(2);
					cout << player.getVY() << endl;
					break;
				case SDLK_LEFT:
					cout << "hey left" << endl;
					player.setVX(-2);
					cout << player.getVX() << endl;
					break;
				}
			}
			else if (SDLEvent.type == SDL_KEYUP) {
				switch (SDLEvent.key.keysym.sym)
				{
				case SDLK_UP:
					cout << "hey up 2" << endl;
					player.setVY(0);
					cout << player.getVY() << endl;
					break;
				case SDLK_RIGHT:
					cout << "hey right 2" << endl;
					player.setVX(0);
					cout << player.getVX() << endl;
					break;
				case SDLK_DOWN:
					cout << "hey down 2" << endl;
					player.setVY(0);
					cout << player.getVY() << endl;
					break;
				case SDLK_LEFT:
					cout << "hey left 2" << endl;
					player.setVX(0);
					cout << player.getVX() << endl;
					break;
				}
			}
		}

		if (frame % 200 == 0) {
			myAnimation.setFrame(animation++);
		}
		if (animation == 4)
			animation = 1;

		//Do the stuffs
		stepAll();

		SDL_FillRect(this->screen, NULL, backgroundColor);//Fill the background color
		SDL_BlitSurface(myAnimation.getSurface(), NULL, screen, &player.getAnimation().getRect());
		SDL_UpdateWindowSurface(this->window);//Update Window

		frame++;
	}
}


//step all of the objects
void StateManager::stepAll() {
	for (int i = 0; i < this->objects.size(); i++) 
	{
		if (this->objects.at(i) != NULL) 
		{
			this->objects.at(i)->step();
		}
	}
	this->player.step();

	//Step all objects
	for (int i = 0; i < objects.size(); i++)
	{
		(this->objects.at(i)->step());
	}


	int count = objects.size();
	//Check for collisions
	for (int i = 0; i < count; i++) {
		GameObject* a = this->objects.at(i);
		for (int j = i + 1; j < count; j++) 
		{
			GameObject* b = this->objects.at(i);
			//Check the team of each pair
			//If the are the same team ask if they touch
			if (a->getTeam() != 0 && b->getTeam() != 0 && (a->getTeam() != b->getTeam() || 
				a->getTeam() == -1)) 
			{
				double x1 = a->getX(), x2 = b->getX(), y1 = a->getY(), y2 = a->getY(),
					w1 = a->getWidth(), w2 = b->getWidth(), h1 = a->getHeight(), 
					h2 = b->getHeight();
				//this might work
				if (x1 < x2 + w2 && x1 + w1 > x2 && 
					y1 < y2 + h2 && y1 + h1 > y2) 
				{
					a->collision();
					b->collision();
				}
			}
		}
	}

	//Remove any objects set to die
	for (int i = 0; i < count; i++) {
		GameObject* o = this->objects.at(i);

		if (o->toDie()) {
			delete o;
			this->objects.at(i) = NULL;
		}
	}
}


//load the map based on the given numbers
//precondition: world (int), level (int)
void StateManager::loadMap(int world, int level) 
{
	
}


//draw all objects who have changes
void StateManager::draw() 
{

}
