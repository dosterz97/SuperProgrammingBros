#include "stdafx.h"
#include "GameObject.h"
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
	this->setWidth(this->animation.getSprite()->getGlobalBounds().width);
	this->setHeight(this->animation.getSprite()->getGlobalBounds().height);

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
	this->setWidth(this->animation.getSprite()->getGlobalBounds().width);
	this->setHeight(this->animation.getSprite()->getGlobalBounds().height);
}


GameObject::~GameObject()
{
}


//set x position
//precondition: double x
void GameObject::setX(double x) 
{
	double moveAmt = this->getAnimation().getSprite()->getGlobalBounds().left;
	this->animation.getSprite()->move(- moveAmt ,0);
	this->animation.getSprite()->move(x, 0);
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
	double moveAmt = this->getAnimation().getSprite()->getGlobalBounds().top;
	this->animation.getSprite()->move(0, - moveAmt);
	this->animation.getSprite()->move(0,y);

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
	sf::FloatRect a = this->getAnimation().getSprite()->getGlobalBounds();
	sf::FloatRect b = o->getAnimation().getSprite()->getGlobalBounds();
	double thisBottom = a.top + a.height, oBottom = b.top + b.height, oRight = b.left + b.width, thisRight = a.left + a.width;

	double bottomCollision = oBottom - a.top, topCollision = thisBottom - b.top, leftCollision = thisRight - b.left, rightCollision = oRight - a.left;

	double max = bottomCollision;
	if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision)
	{
		//bottom collision
		collideBottom(o);
		cout << "bot" << endl;
	}
	else if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision)
	{
		//top collision
		collideTop(o);
		cout << "top" << endl;
	}
	else if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision)
	{
		//right collision
		collideRight(o);
		cout << "rig" << endl;
	}
	else if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < bottomCollision) 
	{
		//left collision
		collideLeft(o);
		cout << "lef" << endl;
	}
}


//left collision logic
void GameObject::collideLeft(GameObject* o)
{
	int distance = this->getAnimation().getSprite()->getGlobalBounds().left - (o->getAnimation().getSprite()->getGlobalBounds().left 
		+ o->getAnimation().getSprite()->getGlobalBounds().width);
	
	this->setX(this->getX() - distance);
	this->setVX(0);
}


//right collision logic
void GameObject::collideRight(GameObject* o)
{
	int distance = this->getAnimation().getSprite()->getGlobalBounds().left + this->getAnimation().getSprite()->getGlobalBounds().width
		- o->getAnimation().getSprite()->getGlobalBounds().left;

	this->setX(this->getX() - distance);
	this->setVX(0);
}


//top collision logic
void GameObject::collideTop(GameObject* o)
{
	int distance = o->getAnimation().getSprite()->getGlobalBounds().top + o->getAnimation().getSprite()->getGlobalBounds().height
		- this->getAnimation().getSprite()->getGlobalBounds().top;

	this->setY(this->getY() + distance);
	this->setVY(0);
}


//top collision logic
void GameObject::collideBottom(GameObject* o)
{
	int distance = this->getAnimation().getSprite()->getGlobalBounds().top + this->getAnimation().getSprite()->getGlobalBounds().height
		- o->getAnimation().getSprite()->getGlobalBounds().top;

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


