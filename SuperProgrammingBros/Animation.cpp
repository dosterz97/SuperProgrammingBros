Animation.cpp
Details
Activity
Animation.cpp
Sharing Info
J

General Info
Type
Text
Size
2 KB (2,168 bytes)
Storage used
0 bytesOwned by someone else
Location
Super Programming Bros
Owner
Jack Allen
Modified
9:12 AM by Jack Allen
Created
9:12 AM
Description
Add a description
Download permissions
Viewers can download

New Team Drive

#include "stdafx.h"
#include "Animation.h"
#include <string>
#include <iostream>
#include "SDL_image.h"

using namespace std;
//create a new animation
//precondition: string of the animation name, bool if the animation is still
Animation::Animation(std::string name, bool isStill, SDL_Renderer* renderer)
{
	this->isStill = isStill;
	this->name = name;
	this->renderer = renderer;

	if (isStill)
	{
		loadSurface(name);
	}
	createTexture();
}


//default constructor
Animation::Animation()
{
	Animation("sasser", true, renderer);
}

Animation::~Animation()
{
}


//load an optimized surface of an image
//precondition: image name
void Animation::loadSurface(std::string path)
{
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

//create the texture (called in the constructor)
//precondition: surface to make from
void Animation::createTexture()
{
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}


//return the image name of the animation
//postcondition: string of the name
std::string Animation::getName()
{
	return name;
}
