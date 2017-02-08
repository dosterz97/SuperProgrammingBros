#pragma once
#include <string>
#include "SDL.h"

class Animation
{
public:
	Animation(std::string, bool);
	Animation();
	~Animation();
	SDL_Surface* getSurface();
	void setStill(bool);
	bool getStill();
	void loadSurface(std::string);
	std::string getName();
	void setFrame(int);
	SDL_Rect getRect();

private:
	int frame;
	std::string name;
	bool isStill;
	SDL_Rect stretchRect;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	void createTexture();
};
