#pragma once
#include <string>
#include "SFML\Graphics.hpp"

class Animation
{
public:
	Animation(std::string, bool);
	Animation();
	~Animation();
	
	void setStill(bool);
	bool getStill();
	std::string getName();
	void setFrame(int);
	sf::Texture* getTexture();
	sf::Sprite* getSprite();
	void loadSprite(std::string);

private:
	int frame;
	std::string name;
	bool isStill;
	sf::Sprite sprite;
	sf::Texture texture;
};
