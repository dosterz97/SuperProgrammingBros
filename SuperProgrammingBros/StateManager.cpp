#include "stdafx.h"
#include "SDL.h"
#include "include\StateManager.h"
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	
	//keep track of the current frame
	int frame = 0;

	high_resolution_clock::time_point start = high_resolution_clock::now();
	

	Uint32 backgroundColor = SDL_MapRGB(screen->format, 0, 0, 0);
	Animation myAnimation("mario-small", true);
	player.setAnimation(myAnimation);
	player.setTeam(1);
	int animation = 1;
	Animation myAnimation2("goomba", true);

	GameObject* t = new GameObject(player, myAnimation2);
	t->setX(200);
	t->setAnimation(myAnimation2);
	objects.push_back(t);
	SDL_Event SDLEvent;
	//Game Loop
	while (!exit)
	{
		high_resolution_clock::time_point thisTime = high_resolution_clock::now();
		//set fps to 20 frames max
		double time_span = (duration_cast<duration<double>>(thisTime - start)).count();
		if (frame * 0.05 < time_span) {

			//cout << "frame: " << frame << endl;
			//cout << "time span: " << time_span << endl;

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
						player.setVY(-30);
						cout << player.getVY() << endl;
						break;
					case SDLK_RIGHT:
						cout << "hey right" << endl;
						player.setVX(5);
						cout << player.getVX() << endl;
						break;
					case SDLK_DOWN:
						cout << "duck" << endl;
						
						break;
					case SDLK_LEFT:
						cout << "hey left" << endl;
						player.setVX(-5);
						cout << player.getVX() << endl;
						break;
					}
				}
				else if (SDLEvent.type == SDL_KEYUP) {
					switch (SDLEvent.key.keysym.sym)
					{
					case SDLK_UP:
						cout << "hey up 2" << endl;
						break;
					case SDLK_RIGHT:
						cout << "hey right 2" << endl;
						player.setVX(0);
						cout << player.getVX() << endl;
						break;
					case SDLK_DOWN:
						cout << "stand" << endl;
						break;
					case SDLK_LEFT:
						cout << "hey left 2" << endl;
						player.setVX(0);
						cout << player.getVX() << endl;
						break;
					}
				}
			}

			if (frame % 5 == 0) {
				myAnimation.setFrame(animation++);
			}
			if (animation == 4)
				animation = 1;

			//Do the stuffs
			stepAll();

			SDL_FillRect(this->screen, NULL, backgroundColor);//Fill the background color
			SDL_BlitSurface(myAnimation.getSurface(), NULL, screen, &objects.at(0)->getAnimation().getRect());
			SDL_BlitSurface(myAnimation.getSurface(), NULL, screen, &player.getAnimation().getRect());
			SDL_UpdateWindowSurface(this->window);//Update Window

			frame++;
		}
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
