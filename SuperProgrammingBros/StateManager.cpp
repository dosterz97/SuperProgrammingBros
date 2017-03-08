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
	Animation myAnimation("koopa", true);
	player = new GameObject(10, 10, myAnimation);
	player->setTeam(1);
	int animation = 1;
	SDL_Event SDLEvent;
	Animation platformA("test",true);
	GameObject* platform = new GameObject(400,190, platformA);
	platform->setTeam(0);
	platform->setVX(0);
	platform->setVY(0);
	objects.push_back(player);
	objects.push_back(platform);

	cout << platform->getWidth() << " , " << platform->getHeight() << endl;
	cout << platform->getAnimation().getRect().w << " , " << platform->getAnimation().getRect().h << endl;

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
						//delete later, so i can fly and test
						//if (player->isGrounded()) {
							player->setGrounded(false);
							player->setVY(-30);
						//}
						break;
					case SDLK_RIGHT:
						player->setVX(5);
						break;
					case SDLK_DOWN:						
						break;
					case SDLK_LEFT:
						player->setVX(-5);
						break;
					}
				}
				else if (SDLEvent.type == SDL_KEYUP) {
					switch (SDLEvent.key.keysym.sym)
					{
					case SDLK_UP:
						break;
					case SDLK_RIGHT:
						player->setVX(0);
						
						break;
					case SDLK_DOWN:
						break;
					case SDLK_LEFT:
						player->setVX(0);
						break;
					}
				}
			}

			if (frame % 5 == 0)
				myAnimation.setFrame(animation++);
			if (animation == 4)
				animation = 1;

			//Do the stuffs
			stepAll();

			SDL_FillRect(this->screen, NULL, backgroundColor);//Fill the background color
			//Draw the stuffs
			for (int i = 0; i < objects.size(); i++) {
				SDL_BlitScaled(objects.at(i)->getAnimation().getSurface(), NULL, screen, &objects.at(i)->getAnimation().getRect());
			}
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
			GameObject* b = this->objects.at(j);
			//Check the team of each pair
			//If the are the same team ask if they touch
			if (a->getTeam() != -1 && b->getTeam() != -1 && (a->getTeam() != b->getTeam())) 
			{
				double x1 = a->getX(), x2 = b->getX(), y1 = a->getY(), y2 = b->getY(),
					w1 = a->getWidth(), w2 = b->getWidth(), h1 = a->getHeight(), 
					h2 = b->getHeight();

				/*cout << "x1 < x2 + w2 : " << x1 << "<" << x2 <<"+"<< w2 << endl;
				cout << "&& x1 + w1 > x2 : " << x1 << "+" << w1 << ">" << x2 << endl;
				cout << "&& y1 < y2 + h2 : " << y1 << "<" << y2 << "+" << h2 << endl;
				cout << "&& y1 + h1 > y2 : " << y1 << "+" << h1 << ">" << y2 << endl;*/
				if (x1 < x2 + w2 && x1 + w1 > x2 && 
					y1 < y2 + h2 && y1 + h1 > y2) 
				{
					a->collision(b);
					b->collision(a);
				}
			}
		}
	}

	//Remove any objects set to die
	//Set grounded to false so they wont float
	for (int i = 0; i < count; i++) {
		GameObject* o = this->objects.at(i);

		if (o->toDie()) {
			delete o;
			this->objects.at(i) = NULL;
		}

		o->setGrounded(false);
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
