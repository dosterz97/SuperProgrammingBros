#include "stdafx.h"
#include "include\GameObject.h"
#include <iostream>

using namespace std;

//Default GameObject constuctor
GameObject::GameObject() {

}

//Put an animation where some object is
//Preconditon: GameObject, Animation
GameObject::GameObject(GameObject object, Animation animation)
{
	this->setAnimation(animation);
	cout << animation.getName() << endl;
	this->setX(object.getX());
	this->setY(object.getY());
	this->setVX(object.getVX());
	this->setVY(object.getVY());
	this->setTeam(object.getTeam());
	this->setToDie(false);
	this->setWidth(this->animation.getRect().w);
	this->setHeight(this->animation.getRect().h);

}

//Create a new GameObject
//Precondition: x position, y position, object animation
GameObject::GameObject(double x, double y, Animation animation) 
{
	this->animation = animation;
	this->setX(x);
	this->setY(y);
	this->setVX(0);
	this->setVY(0);
	this->setTeam(1);
	this->setToDie(false);
	this->setWidth(this->animation.getRect().w);
	this->setHeight(this->animation.getRect().h);
}


GameObject::~GameObject()
{
}


//set x position
//precondition: double x
void GameObject::setX(double x) 
{
	this->x = x;
	SDL_Rect newRect = this->animation.getRect();
	newRect.x = this->x;
	this->animation.setRect(newRect);
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
	SDL_Rect newRect = this->animation.getRect();
	newRect.y = this->y;
	this->animation.setRect(newRect);
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
	if (this->team != 0) {
		//apply gravity  
		if ((team != 0 || team != -1) && this->YVelocity <= 18) {
			this->YVelocity += 6;
		}

		if (this->isGrounded()) {
			this->YVelocity = 0;
		}

		//apply velocity
		this->setX(x + XVelocity);
		//terminal velocity
		if (YVelocity > 18) {
			YVelocity = 18;
		}
		if (y < 500 || YVelocity < 0) {
			this->setY(y + YVelocity);
		}

		//go to next animation
		this->nextAnimation(this->getAnimation());
	}
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
void GameObject::collision(GameObject* other)
{
	switch (team) {
	case -1:	
		break;
	case 0:
		break;
	case 1:
		collisionSide(other);
		break;
	case 2: 
		cout << "i am a powerup" << endl;
		
		break;
	}
}


//returns a number based on which collision is the most prominent
//If there is a collision, the function calls the collision side function
//Postcondition: 0-Top 1-Right 2-Bottom 3-Left
void GameObject::collisionSide(GameObject* o) {
	SDL_Rect a = this->getAnimation().getRect();
	SDL_Rect b = o->getAnimation().getRect();
	double thisBottom = a.y + a.h, oBottom = b.y + b.h, oRight = b.x + b.w, thisRight = a.x + a.w;

	double bottomCollision = oBottom - a.y, topCollision = thisBottom - b.y, leftCollision = thisRight - b.x, rightCollision = oRight - a.x;

	double max = bottomCollision;
	if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
	{
		//bottom collision
		collideBottom(o);
	}
	else if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
	{
		//top collision
		collideTop(o);
	}
	else if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
	{
		//right collision
		collideRight(o);
	}
	else if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision) 
	{
		//left collision
		collideLeft(o);
	}
}


//left collision logic
void GameObject::collideLeft(GameObject* o)
{
	int distance = this->getAnimation().getRect().x - o->getAnimation().getRect().x + o->getAnimation().getRect().w;
	
	this->setX(this->getX() + distance);
	this->setVX(0);
}


//right collision logic
void GameObject::collideRight(GameObject* o)
{
	int distance = this->getAnimation().getRect().x + this->getAnimation().getRect().w - o->getAnimation().getRect().x;

	this->setX(this->getX() - distance);
	this->setVX(0);
}


//top collision logic
void GameObject::collideTop(GameObject* o)
{
	int distance = o->getAnimation().getRect().y + o->getAnimation().getRect().h - this->getAnimation().getRect().y;

	this->setY(this->getY() + distance);
	this->setVY(0);
}


//top collision logic
void GameObject::collideBottom(GameObject* o)
{
	int distance = this->getAnimation().getRect().y + this->getAnimation().getRect().h - o->getAnimation().getRect().y;

	this->grounded = true;

	this->setY(this->getY() - distance);
	this->setVY(0);
}


//get the grounded variable
//postcondition: bool
bool GameObject::isGrounded() 
{
	return this->grounded;
}


//set the grounded variable
//precondition: bool
void GameObject::setGrounded(bool grounded)
{
	this->grounded = grounded;
}


