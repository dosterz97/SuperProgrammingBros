#include "stdafx.h"
#include "StateManager.h"
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

StateManager::StateManager(sf::RenderWindow* window) 
{
	this->window = window;
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
	

	Animation myAnimation("mario", true);
	player = new GameObject(300, 0, myAnimation);
	player->setTeam(1);
	int animation = 1;
	Animation platformA("test",true);
	GameObject* platform = new GameObject(400,0, platformA);
	platform->setTeam(0);
	objects.push_back(player);
	objects.push_back(platform);


	//Game Loop
	while (!exit)
	{
		high_resolution_clock::time_point thisTime = high_resolution_clock::now();
		//set fps to 20 frames max
		double time_span = (duration_cast<duration<double>>(thisTime - start)).count();
		
		if (frame * 0.05 < time_span)
		{

			cout << "frame: " << frame << endl;
			cout << "time span: " << time_span << endl;
				sf::Event event;
				while (window->pollEvent(event))
				{

					if (event.type == sf::Event::Closed)
						return;
					if (event.type == sf::Event::KeyPressed) {
						switch (event.key.code)
						{
						case sf::Keyboard::Up:
							//delete later, so i can fly and test
							//if (player->isGrounded()) {
							player->setGrounded(false);
							player->setVY(-30);
							//}
							break;
						case sf::Keyboard::Right:
							player->setVX(5);
							break;
						case sf::Keyboard::Down:
							break;
						case sf::Keyboard::Left:
							player->setVX(-5);
							break;
						}
					}
					else if (event.type == sf::Event::KeyReleased) {
						switch (event.key.code)
						{
						case sf::Keyboard::Up:
							break;
						case sf::Keyboard::Right:
							player->setVX(0);
							break;
						case sf::Keyboard::Down:
							break;
						case sf::Keyboard::Left:
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

			//Draw everything to the window
			window->clear();
			for (int i = 0; i < objects.size(); i++)
			{
				window->draw(*objects.at(i)->getAnimation().getSprite());
			}
			window->display();
			frame++;
		}
	}
}


//step all of the objects
void StateManager::stepAll() 
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		if (this->objects.at(i) != NULL)
		{
			this->objects.at(i)->step();
		}
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
