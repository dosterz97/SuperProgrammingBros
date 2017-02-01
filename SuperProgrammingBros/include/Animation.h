#pragma once
#include <string>
#include "SDL.h"

class Animation
{
public:
	Animation(std::string, bool, SDL_Renderer*);
	Animation();
	~Animation();
	SDL_Surface* getSurface();
	void setStill(bool);
	bool getStill();
	void loadSurface(std::string);
	std::string getName();
	
private:
	std::string name;
	bool isStill;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	void createTexture();
};
