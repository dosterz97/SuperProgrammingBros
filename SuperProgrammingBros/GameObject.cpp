#include "stdafx.h"
#include "include\GameObject.h"


//Default GameObject constuctor
GameObject::GameObject() {

}

//Put an animation where some object is
//Preconditon: GameObject, Animation
GameObject::GameObject(GameObject object, Animation animation)
{
	this->setAnimation(animation);
	this->setX(object.getX());
	this->setY(object.getY());
	this->setVX(object.getVX());
	this->setVY(object.getVY());
	this->setTeam(object.getTeam());
	this->setToDie(false);
}

//Create a new GameObject
//Precondition: x position, y position, object animation
GameObject::GameObject(double x, double y, Animation animation) 
{
	this->x = x;
	this->y = y;
	this->animation = animation;
	this->setVX(0);
	this->setVY(0);
	this->setTeam(0);
	this->setToDie(false);
}


GameObject::~GameObject()
{
}


//set x position
//precondition: double x
void GameObject::setX(double x) 
{
	this->x = x;
}


//get y position
//postcondition: double y 
double GameObject::getX() 
{
	return x;
}


//set y position
//precondition: double y
void GameObject::setY(double y) 
{
	this->y = y;
}


//get y position
//postcondition: double y 
double GameObject::getY() 
{
	return y;
}


//set x velocity
//precondition: double x
void GameObject::setVX(double XVelocity) 
{
	this->XVelocity = XVelocity;
}


//get x velocity
//postcondition: double x 
double GameObject::getVX() 
{
	return XVelocity;
}


//set x velocity
//precondition: double x
void GameObject::setVY(double YVelocity) 
{
	this->YVelocity = YVelocity;
}


//get x velocity
//postcondition: double x 
double GameObject::getVY() 
{
	return YVelocity;
}


//set animation
//precondition: double x
void GameObject::setAnimation(Animation animation) 
{
	this->animation = animation;
}


//get animation
//postcondition: Animation
Animation GameObject::getAnimation() 
{
	return animation;
}


//set the objects to die
//precondition: bool
void GameObject::setToDie(bool dead) 
{
	this->dead = dead;
}


//get whethere the object is dead
//postcondition: bool
bool GameObject::toDie() 
{
	return dead;
}


//do on frame of logic for the object
void GameObject::step() 
{
	//apply velocity
	this->setX(this->getX() + this->getVX());
	this->setY(this->getY() + this->getVY());

	//go to next animation
	this->nextAnimation(this->getAnimation());

	//check collisions

}


//get the objects team
//postcondition: int
int GameObject::getTeam() 
{
	return team;
}


//set the team of the object
//0 interacts with nothing 1 is neutral 
//2 is player 3 is an enemy
//Precondition: int
void GameObject::setTeam(int newTeam) 
{
	this->team = newTeam;
}


//move to the next animation based upon what animation was given
//precondition: Animation
void GameObject::nextAnimation(Animation currentAnimation) 
{
	
}


//Set the height of the object not the sprite
//precondition: double
void GameObject::setHeight(double height) 
{
	this->height = height;
}


//get the height of the object
//post condition: double
double GameObject::getHeight() 
{
	return height;
}


//set the width of the object not the sprite
//precondition: double
void GameObject::setWidth(double width) 
{
	this->width = width;
}


//get the width of the object
//post condition: double
double GameObject::getWidth() 
{
	return width;
}


//do the collision logic for the object
void GameObject::collision()
{

}
