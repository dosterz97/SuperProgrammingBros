#pragma once

#include "include\Animation.h"

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
	Animation getAnimation();
	void setToDie(bool);
	bool toDie();
	void setTeam(int);
	int getTeam();

	void step();//move things one 'step' or frame
	
	void nextAnimation(Animation);
private: 
	double x,y;//cordinate
	double XVelocity, YVelocity;
	int team;

	bool dead = false;//will remove in state manager if true

	Animation animation;//object animation
};

