#pragma once

#include <vector>
#include "GameObject.h"
#include "SFML\Graphics.hpp"

using namespace std;

class StateManager
{
public:
	StateManager(sf::RenderWindow*);
	~StateManager();

	void handleEvents();
	void stepAll(int);
	void loadMap(string mapToLoad = "1\\1");
	void draw();
	void createObject(int, int, int, int);
private:
	int world=1;
	int level=1;
	
	sf::RenderWindow* window;
	GameObject* player;
	Animation createObjectTempAnimation;
	vector<GameObject*> objects;

	//the camera to follow the player
	sf::View* view;

	
};

