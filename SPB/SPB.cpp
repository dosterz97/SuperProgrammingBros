// SPB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "StateManager.h"
using namespace std;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Super Mario Bros!");
	
	StateManager* myMan = new StateManager(&window);
	myMan->handleEvents();
	window.close();
	return 0;
}

