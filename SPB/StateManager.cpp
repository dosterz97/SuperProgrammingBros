#include "stdafx.h"
#include "StateManager.h"

#include <fstream>
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

	double scale = 0;


	Animation mapAnimation("maps\\1", true);
	GameObject* map = new GameObject(0, 0, mapAnimation);
	map->getAnimation()->getSprite()->setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	map->setTeam(-1);
	objects.push_back(map);

	//loadMap();

	Animation myAnimation("mario", true, 3);
	player = new GameObject(200, 0, myAnimation);
	player->setTeam(1);
	int animation = 1;
	objects.push_back(player);

	
	view = new sf::View(sf::FloatRect(player->getX() - SCREEN_WIDTH / 2, player->getY() -
	SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT));

	high_resolution_clock::time_point start = high_resolution_clock::now();

	//Game Loop
	while (!exit)
	{
		high_resolution_clock::time_point thisTime = high_resolution_clock::now();
		//set fps to 20 frames max
		double time_span = (duration_cast<duration<double>>(thisTime - start)).count();
		
		if (frame * 0.05 < time_span)
		{

			//cout << "frame: " << frame << endl;
			//cout << "time span: " << time_span << endl;
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
								player->setVY(-46);
							//}
							break;
						case sf::Keyboard::Right:
							player->setVX(10);
							player->setMoving(true);
							//player->setFlipped(false);
							break;
						case sf::Keyboard::Down:
							break;
						case sf::Keyboard::Left:
							player->setVX(-10);
							player->setMoving(true);
							//player->setFlipped(true);
							break;
						}
					}
					else if (event.type == sf::Event::KeyReleased) {
						switch (event.key.code)
						{
						case sf::Keyboard::Up:
							player->getAnimation()->setFrame(1);
							break;
						case sf::Keyboard::Right:
							player->setVX(0);
							player->getAnimation()->setFrame(1);
							player->setMoving(false);
							break;
						case sf::Keyboard::Down:
							player->getAnimation()->setFrame(1);
							break;
						case sf::Keyboard::Left:
							player->setVX(0);
							player->getAnimation()->setFrame(1);
							player->setMoving(false);
							break;
						}
					}
				}
				

			

			//Do the stuffs 
			stepAll(frame);

			window->clear();

			//set up the default texture for the background
			//divide pos by 2 because scale
			scale = 2;
			objects.at(0)->textureRect((player->getX() - SCREEN_WIDTH / 2) / scale, player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
			map->getAnimation()->getSprite()->setPosition(sf::Vector2f(player->getX() - SCREEN_WIDTH / 2, - SCREEN_HEIGHT / 2));

			//set up the view
			view->move(sf::Vector2f(-view->getCenter().x + player->getX() + player->getWidth() / 2
				, -view->getCenter().y + player->getY() + player->getHeight() / 2));

			//set up view for side of map
			if (view->getCenter().x - SCREEN_WIDTH / 2 < 0) 
			{
				view->setCenter(sf::Vector2f(SCREEN_WIDTH / 2, view->getCenter().y));
				objects.at(0)->textureRect(- SCREEN_WIDTH / 2, player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
				map->getAnimation()->getSprite()->setPosition(sf::Vector2f(0, - SCREEN_HEIGHT / 2));
			}
			if (view->getCenter().x + SCREEN_WIDTH/2 > map->getAnimation()->getTexture()->getSize().x * scale)
			{
				view->setCenter(sf::Vector2f(map->getAnimation()->getTexture()->getSize().x * scale -SCREEN_WIDTH/2, view->getCenter().y));
				objects.at(0)->textureRect(map->getAnimation()->getTexture()->getSize().x -SCREEN_WIDTH /2,
					player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
				map->getAnimation()->getSprite()->setPosition(sf::Vector2f(map->getAnimation()->getTexture()->getSize().x * scale - SCREEN_WIDTH
					, -SCREEN_HEIGHT / 2));
			}
			window->setView(*view);//attach the view
			
			//draw everything
			for (int i = 0; i < objects.size(); i++)
			{
				window->draw(*objects.at(i)->getAnimation()->getSprite());
			}

			//Draw everything to the window
			window->display();

			frame++;//done, go/wait for next frame
		}
	}
}


//step all of the objects
void StateManager::stepAll(int frame) 
{
	for (int i = 0; i < objects.size(); i++)
	{
		//step object
		if (objects.at(i) != NULL)
		{
			 objects.at(i)->step();

			//move animation
			if (objects.at(i)->isMoving() && frame % 4 == 0) {
				objects.at(i)->nextAnimation();
			}
		}
	}


	int count = objects.size();
	
	//Check for collisions
	for (int i = 0; i < count; i++) {
		GameObject* a =  objects.at(i);
		for (int j = i + 1; j < count; j++) 
		{
			GameObject* b =  objects.at(j);
			//Check the team of each pair
			//If the are the same team ask if they touch
			if (a->getTeam() != -1 && b->getTeam() != -1 && (a->getTeam() != b->getTeam())) 
			{
				double x1 = a->getX(), x2 = b->getX(), y1 = a->getY(), y2 = b->getY(),
					w1 = a->getWidth(), w2 = b->getWidth(), h1 = a->getHeight(), 
					h2 = b->getHeight();
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
		GameObject* o =  objects.at(i);

		if (o->toDie()) {
			delete o;
			 objects.at(i) = NULL;
		}

		o->setGrounded(false);
	}
}


//load the map based on the given numbers
//precondition: world (int), level (int)
void StateManager::loadMap(string mapToLoad) 
{
	ifstream file;
	file.open("maps\\" + mapToLoad + ".txt");

	string entity;
	string x, y, type, team;
	int counter = 0, stringCounter = 0;
	bool isSpace = false;
	while (getline(file, entity)) {
		cout << entity << endl;
		counter = 0;
		stringCounter = 0;
		
		do
		{
			if (entity.length() == stringCounter) 
			{
				cout << "entity length reached" << endl;
				createObject(stoi(x), stoi(y), stoi(type), stoi(team));
				x = "", y = "", type = "", team = "";
				break;
			}
			if (entity.substr(stringCounter, 1) == " ") 
			{
				counter++;
				isSpace = true;
			}
			if (!isSpace) {
				switch (counter)
				{
				case 0:
					x += entity.substr(stringCounter, 1);
					break;
				case 1:
					y += entity.substr(stringCounter, 1);
					break;
				case 2:
					type += entity.substr(stringCounter, 1);
					break;
				case 3:
					team += entity.substr(stringCounter, 1);
					break;
				default:
					break;
				}
			}
			stringCounter++;
			isSpace = false;
		} while (counter <= 4);
	}
	file.close();
}


//draw all objects who have changes
void StateManager::draw() 
{

}

//creates the objects 
//pre condition: 
void StateManager::createObject(int x, int y, int type, int team)
{
	cout << "x: " << x << " y: " << y << " type: " << type << " team: " << team << endl;
	
	createObjectTempAnimation = Animation("mario", true, 3);
	GameObject* object = new GameObject(16 * 2 * x, 16 * 2 * y, createObjectTempAnimation);
	object->setTeam(team);
	object->setAnimation(createObjectTempAnimation);
	objects.push_back(object);
}
