#pragma once

#include <vector>
#include "include\GameObject.h"

using namespace std;

class StateManager
{
public:
	StateManager();
	StateManager(SDL_Window*, SDL_Surface*);
	~StateManager();

	void handleEvents();
	void stepAll();
	void loadMap(int, int);
	void draw();
private:
	int world=1;
	int level=1;
	SDL_Window* window;
	SDL_Surface* screen;
	GameObject* player;
	vector<GameObject*> objects;
};

