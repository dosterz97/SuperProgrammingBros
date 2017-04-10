#include "stdafx.h"
#include "StateManager.h"
#include "Block.h"
#include "Koopa.h"

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

	setupAnimations();

	myCoinAnimation = new Animation("coin", true);
	myShroom = new Animation("flower", true, 1);

	Animation mapAnimation("maps\\1", true);
	GameObject* map = new GameObject(0, 0, mapAnimation, frame);
	map->getAnimation()->getSprite()->setTextureRect(sf::IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	map->setTeam(-1);
	objects.push_back(map);

	loadMap();

	player = new GameObject(3000, 0, *animations[8], frame);
	player->setTeam(1);
	int animation = 1;
	objects.push_back(player);

	/*Block* block = new Block(512, -28, *animations[0], frame);
	block->setTeam(0);
	block->setCoins(3);
	block->setPowerUp(0);
	objects.push_back(block);*/

	/*Koopa* monster = new Koopa(500, 0, *animations[10], frame , *animations[11]);
	monster->setTeam(3);
	objects.push_back(monster);*/




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
			stepAll(frame, &objects);

			window->clear();

			//set up the default texture for the background
			//divide pos by 2 because scale
			scale = 2;
			objects.at(0)->textureRect((player->getX() - SCREEN_WIDTH / 2) / scale, player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
			map->getAnimation()->getSprite()->setPosition(sf::Vector2f(player->getX() - SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2));

			//set up the view
			view->move(sf::Vector2f(-view->getCenter().x + player->getX() + player->getWidth() / 2, 0));

			//set up view for side of map
			if (view->getCenter().x - SCREEN_WIDTH / 2 < 0)
			{
				view->setCenter(sf::Vector2f(SCREEN_WIDTH / 2, view->getCenter().y));
				objects.at(0)->textureRect(-SCREEN_WIDTH / 2, player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
				map->getAnimation()->getSprite()->setPosition(sf::Vector2f(0, -SCREEN_HEIGHT / 2));
			}
			if (view->getCenter().x + SCREEN_WIDTH / 2 > map->getAnimation()->getTexture()->getSize().x * scale)
			{
				view->setCenter(sf::Vector2f(map->getAnimation()->getTexture()->getSize().x * scale - SCREEN_WIDTH / 2, view->getCenter().y));
				objects.at(0)->textureRect(map->getAnimation()->getTexture()->getSize().x - SCREEN_WIDTH / 2,
					player->getY() - SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
				map->getAnimation()->getSprite()->setPosition(sf::Vector2f(map->getAnimation()->getTexture()->getSize().x * scale - SCREEN_WIDTH
					, -SCREEN_HEIGHT / 2));
			}
			window->setView(*view);//attach the view

			objects.shrink_to_fit();
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
void StateManager::stepAll(int frame, vector<GameObject*>* objects)
{
	for (int i = 0; i < objects->size(); i++)
	{
		//step object
		if (objects->at(i) != NULL)
		{
			objects->at(i)->step(objects);

			//TODO: Change the frame % to dynamic number
			//move animation
			if (objects->at(i)->isMoving() && frame % 4 == 0) {
				objects->at(i)->nextAnimation();
			}
		}
	}

	//move blocks back down
	for (int i = 0; i < objects->size(); i++) {
		if (objects->at(i) != NULL && objects->at(i)->getTeam() == 0 && objects->at(i)->isMoving())
		{
			objects->at(i)->setVY(objects->at(i)->getVY() + 1);
			//Stop block
			if (objects->at(i)->getVY() == 4)
			{
				if (objects->at(i)->getCoins() > 0)
				{
					coin->setToDie(true);
					objects->at(i)->setCoins(objects->at(i)->getCoins() - 1);
				}
				objects->at(i)->setMoving(false);
				objects->at(i)->setVY(0);
			}

			//release powerup
			if (objects->at(i)->getVY() == -1)
			{
				if (objects->at(i)->getCoins() > 0)
				{
					coin = new GameObject(*objects->at(i), *myCoinAnimation, frame);
					coin->setY(coin->getY() - 32);//move above the block
					coin->setX(coin->getX() + 6);//offset block size
					coin->setVY(0);//block has velocity
					objects->push_back(coin);
				}
				if(objects->at(i)->getCoins() == 1)
				{
					objects->at(i)->setAnimation(*animations[1]);
					objects->at(i)->getAnimation()->getSprite()->
						setPosition(sf::Vector2f(objects->at(i)->getX(), objects->at(i)->getY()));
				}
				if (objects->at(i)->getPowerUp() == 1)
				{
					powerup = new GameObject(*objects->at(i), *myShroom, frame);
					powerup->setY(powerup->getY() - 32);
					powerup->setTeam(2);
					objects->at(i)->setPowerUp(0);
					objects->push_back(powerup);
					objects->at(i)->setAnimation(*animations[1]);
					objects->at(i)->getAnimation()->getSprite()->
						setPosition(sf::Vector2f(objects->at(i)->getX(), objects->at(i)->getY()));
				}
				else if (objects->at(i)->getPowerUp() == 2)
				{
					powerup = new GameObject(*objects->at(i), *myShroom, frame);
					powerup->setY(powerup->getY() - 32);
					powerup->setTeam(2);
					objects->at(i)->setPowerUp(0);
					objects->push_back(powerup);
					objects->at(i)->setAnimation(*animations[1]);
					objects->at(i)->getAnimation()->getSprite()->
						setPosition(sf::Vector2f(objects->at(i)->getX(), objects->at(i)->getY()));
				}
			}

		}
	}


	int count = objects->size();

	//Check for collisions
	for (int i = 0; i < count; i++) {
		GameObject* a = objects->at(i);
		for (int j = i + 1; j < count; j++)
		{
			GameObject* b = objects->at(j);
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
					a->collision(b, animations);
					b->collision(a, animations);
				}
			}
		}
	}

	//Remove any objects set to die
	//Set grounded to false so they wont float
	int offset = 0;
	for (int i = 0; i < count-offset; i++)
	{
		objects->at(i-offset)->setGrounded(false);

		if (objects->at(i- offset)->toDie())
		{
			delete objects->at(i - offset);
			objects->erase(objects->begin() + i - offset);
			offset++;
		}
	}
	objects->shrink_to_fit();
}

void StateManager::setupAnimations()
{
	animations[0] = new Animation("question-block");
	animations[1] = new Animation("used-block");
	animations[2] = new Animation("block");
	animations[3] = new Animation("underground-block");
	animations[4] = new Animation("underground-used-block");
	animations[5] = new Animation("castle-block");
	animations[6] = new Animation("castle-used-block");
	animations[7] = new Animation("mario-small");
	animations[8] = new Animation("mario");
	animations[9] = new Animation("goomba");
	animations[10] = new Animation("koopa");
	animations[11] = new Animation("koopa-shell" , 2);
	animations[12] = new Animation("ground-block");
	animations[13] = new Animation("stair-block");
}


//load the map based on the given numbers
//precondition: world (int), level (int)
void StateManager::loadMap(string mapToLoad)
{
	ifstream file;
	file.open("maps\\" + mapToLoad + ".txt");

	string entity;
	string x, y, type, team, width,height;
	int counter = 0, stringCounter = 0;
	bool isSpace = false;
	while (getline(file, entity)) {
		counter = 0;
		stringCounter = 0;

		do
		{
			if (entity.length() == stringCounter)
			{
				//cout << "entity length reached" << endl;
				if (width == "" || height == "")
				{
					width = "16";
					height = "16";
				}
				createObject(stoi(x), stoi(y), stoi(type), stoi(team), stoi(width), stoi(height));
				x = "", y = "", type = "", team = "", height ="", width = "";
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
				case 4:
					width += entity.substr(stringCounter, 1);
					break;
				case 5:
					height += entity.substr(stringCounter, 1);
					break;
				default:
					break;
				}
			}
			stringCounter++;
			isSpace = false;
		} while (counter <= 5);
	}
	file.close();
}


//draw all objects who have changes
void StateManager::draw()
{

}

//creates the objects 
//pre condition: 
void StateManager::createObject(int x, int y, int type, int team, int width, int height)
{
	
	if (team == 0) {
		//cout << "x: " << x << " y: " << y << " type: " << type << " team: " << team << " width: " <<
		//	width << " height: " << height << endl;
		Block* block = new Block(16 * 2 * x, 16 * 2 * y-412, *animations[type], 0);
		if (width != 16 || height != 16) {
			block->getAnimation()->getSprite()->setTextureRect(sf::IntRect(0, 0, width, height));
			block->setWidth(width*2);
			block->setHeight(height*2);
		}
		block->setTeam(0);
		block->setCoins(0);
		block->setPowerUp(0);
		cout << "x: " << block->getX() << " y: " << block->getY() << " width: " << block->getWidth() << " height: " << block->getHeight() << endl;
		objects.push_back(block);
	}
	else {
		GameObject* object = new GameObject(width * 2 * x, height * 2 * y, *animations[type], 0);
		object->setTeam(team);
		objects.push_back(object);
	}
}
