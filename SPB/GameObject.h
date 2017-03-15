#pragma once

#include "Animation.h"

class GameObject
{
public:
	GameObject();
	GameObject(GameObject, Animation);//Place a new animation where an object was
	GameObject(double, double, Animation);
	~GameObject();

	//gets and sets for instance variables
	void setX(double);
	double getX();
	void setY(double);
	double getY();
	void setVX(double);
	double getVX();
	void setVY(double);
	double getVY();
	void setAnimation(Animation animation);
	Animation* getAnimation();
	void setToDie(bool);
	bool toDie();
	void setTeam(int);
	int getTeam();
	void setHeight(double);
	double getHeight();
	void setWidth(double);
	double getWidth();
	void setGrounded(bool);
	bool isGrounded();

	//move things one 'step' or frame
	void step();
	//called when State Manager finds a collision between objects
	void collision(GameObject*);
	//move to the next animation given an animation
	void nextAnimation(Animation);
	//determines which side the collision occured on
	void collisionSide(GameObject*);

	//set texture rect
	void textureRect(int x = 0, int y = 0, int w = -1, int h = -1);
	
	//executes the specific logic for the side that has been determined by collisionSide
	//the reason I have these functions is so that they can be overriden
	//and different functionality can be made for different classes
	void collideLeft(GameObject*);
	void collideRight(GameObject*);
	void collideTop(GameObject*);
	void collideBottom(GameObject*);

private: 
	double x,y;//cordinate
	double width, height;//size
	double XVelocity, YVelocity;

	int team;

	bool dead = false;//will remove in state manager if true
	bool grounded = false;

	Animation animation;//object animation
};

