#pragma once
#include <string>
#include "SFML\Graphics.hpp"

class Animation
{
public:
	Animation(std::string, bool isStill = true ,int frames = 1);
	Animation();
	~Animation();
	
	void setStill(bool);
	bool getStill();
	std::string getName();
	void setFrame(int);
	int getCurrentFrame();
	sf::Texture* getTexture();
	sf::Sprite* getSprite();
	int getFrames();

	//actual loading of the image
	void loadSprite(std::string, int x = 0, int y = 0, int w = -1, int h = -1);

private:
	int frame;
	int frames;//how many frames for the animations
	std::string name;
	std::string oldpath= "";
	bool isStill;
	sf::Sprite sprite;
	sf::Texture texture;
};
