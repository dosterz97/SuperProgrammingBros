#include "stdafx.h"
#include "Animation.h"
#include <string>
#include <iostream>

using namespace std;
//create a new animation
//precondition: string of the animation name, bool if the animation is still
Animation::Animation(std::string name, bool isStill)
{
	this->isStill = isStill;
	this->name = name;
	this->frame = 1;
	if (isStill)
		loadSprite(name);
}

//default constructor
//postcondition: a new animation object
Animation::Animation()
{
	Animation("default", true);
}

Animation::~Animation()
{

}


//load an optimized surface of an image
//precondition: image name
void Animation::loadSprite(std::string path, int x, int y, int w, int h)
{
	//create string of frame to modify path
	string frameStr = to_string(frame);

	
	//modify the string so it pulls an image from the "images" file
	path = "images\\" + path + "-"+ frameStr +".png";
	if (path != oldpath) {
		if (w == -1 || h == -1) {
			if (!texture.loadFromFile(path)) {}
		}
		else
		{
			if (!texture.loadFromFile(path, sf::IntRect(x, y, w, h))) {}
		}
	}
	oldpath = path;
	sprite.setTexture(texture);
	sprite.scale(2, 2);
	return;
}


//return the set surface
//postcondition: pointer to a surface
sf::Texture* Animation::getTexture()
{
	return &texture;
}


//return if the animation is still
//postcondition: bool if the animation is still
bool Animation::getStill()
{
	return isStill;
}


//set if the animation is still
//precondition: bool for if the animation is still
void Animation::setStill(bool isStill)
{
	this->isStill = isStill;
}

//return the image name of the animation
//postcondition: string of the name
std::string Animation::getName()
{
	return name;
}

//change the frame of the image
//precondition: the frame to change
void Animation::setFrame(int frame)
{
	this->frame = frame;
	loadSprite(name);

	return;
}

//get the stretched rect
//postcondition: a stretched rect
sf::Sprite* Animation::getSprite()
{
	return &sprite;
}

