#include "stdafx.h"
#include "include\Animation.h"
#include <string>
#include <iostream>
#include "SDL_image.h"

using namespace std;
//create a new animation
//precondition: string of the animation name, bool if the animation is still
Animation::Animation(std::string name, bool isStill)
{
	this->isStill = isStill;
	this->name = name;
	this->frame = 1;
	if (isStill)
		loadSurface(name);
}

//default constructor
//postcondition: a new animation object
Animation::Animation()
{
	Animation("mario", true);
}

Animation::~Animation()
{

}


//load an optimized surface of an image
//precondition: image name
void Animation::loadSurface(std::string path)
{
	//create string of frame to modify path
	string frameStr = to_string(frame);

	//modify the string so it pulls an image from the "images" file
	path = "images\\" + path + "-"+ frameStr +".png";

	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image %s! SDL Error: %s\n" << path.c_str() << SDL_GetError();
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, loadedSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			cout<< "Unable to optimize image %s! SDL Error: %s\n" <<
				path.c_str() << SDL_GetError();
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	this-> surface = optimizedSurface;

	return;
}


//return the set surface
//postcondition: pointer to a surface
SDL_Surface* Animation::getSurface()
{
	return surface;
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
	loadSurface(name);

	return;
}