#include "stdafx.h"
#include "GameObject.h"
#include <iostream>
#include "Block.h"

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
	animation.getSprite()->setPosition(x, animation.getSprite()->getGlobalBounds().top);
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
	animation.getSprite()->setPosition(animation.getSprite()->getGlobalBounds().left, y);
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
Animation* GameObject::getAnimation() 
{
	return &animation;
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
	if (this-team != 0 && team != -1) {
		//apply gravity  
		if ((team != 0 && team != -1) && this->YVelocity <= 18) {
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
		if (y < 36 || YVelocity < 0) {
			this->setY(y + YVelocity);
		}
		if (y > 36) {
			this->setY(36);
		}
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
void GameObject::nextAnimation() 
{
	if (animation.getFrames() == animation.getCurrentFrame()) {
		//reset counter to 1
		animation.setFrame(1);
	}
	else {
		animation.setFrame(animation.getCurrentFrame() + 1);
	}
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
		collisionSide(other);
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
	sf::FloatRect a = animation.getSprite()->getGlobalBounds();
	sf::FloatRect b = o->getAnimation()->getSprite()->getGlobalBounds();
	double thisBottom = a.top + a.height, oBottom = b.top + b.height, oRight = b.left + b.width, thisRight = a.left + a.width;

	double bottomCollision = oBottom - a.top, topCollision = thisBottom - b.top, leftCollision = thisRight - b.left, rightCollision = oRight - a.left;

	double max = bottomCollision;

	/*cout << "bottom collision: " << bottomCollision << endl;
	cout << "top collision: " << topCollision << endl;
	cout << "left collision: " << leftCollision << endl;
	cout << "right collision: " << rightCollision << endl;*/

	//find the maximum infraction into the oppossing object
	if (topCollision > max) {
		max = topCollision;
	}
	if (leftCollision > max) {
		max = leftCollision;
	}
	if (rightCollision > max) {
		max = rightCollision;
	}
	if (topCollision == max)
	{
		//top collision
		collideTop(o);
		cout << "top" << endl;
	}
	else if (bottomCollision==max)
	{
		//bottom collision

		//cast to block call different collide bottom
		if (this->team == 0) {
			try {
				Block* c = dynamic_cast<Block*>(this);
				c->collideBottom(o);
			}
			catch (int n){
				cout << "failed to cast from GameObject to Block" << endl;
			}
		}
		else {
			collideBottom(o);
			cout << "bot" << endl;
		}
	}
	if (rightCollision == max)
	{
		//right collision
		collideRight(o);
		cout << "rig" << endl;
	}
	else if (leftCollision == max)
	{
		//left collision
		collideLeft(o);
		cout << "lef" << endl;
	}
}

void GameObject::textureRect(int x, int y, int w, int h)
{
	
	if (h == -1) 
	{
		h = animation.getTexture()->getSize().y;
	}
	if (w == -1)
	{
		w = animation.getTexture()->getSize().x;
	}
	
	if (x < 0) 
	{
		x = 0;
	}
	if (y < 0) 
	{
		y = 0;
	}
	//cout << animation.getTexture()->getSize().x << ", " << animation.getTexture()->getSize().y << endl;
	/*
	if (x + w > animation.getTexture()->getSize().x) 
	{
		w = animation.getTexture()->getSize().x - x;
	}
	if (y + h > animation.getTexture()->getSize().y) 
	{
		w = animation.getTexture()->getSize().y - h;
	}
	*/

	animation.getSprite()->setTextureRect(sf::IntRect(x, y, w, h));
	this->width = 2*w;
	this->height = 2*h;
}


//left collision logic
void GameObject::collideLeft(GameObject* o)
{
	int distance = animation.getSprite()->getGlobalBounds().left - (o->getAnimation()->getSprite()->getGlobalBounds().left
		+ o->getAnimation()->getSprite()->getGlobalBounds().width);
	this->setX(this->getX() - distance);
	this->setVX(0);
}


//right collision logic
void GameObject::collideRight(GameObject* o)
{
	int distance = animation.getSprite()->getGlobalBounds().left + animation.getSprite()->getGlobalBounds().width
		- o->getAnimation()->getSprite()->getGlobalBounds().left;
	this->setX(this->getX() - distance);
	this->setVX(0);
}


//top collision logic
void GameObject::collideTop(GameObject* o)
{
	int distance = o->getAnimation()->getSprite()->getGlobalBounds().top + o->getAnimation()->getSprite()->getGlobalBounds().height
		- animation.getSprite()->getGlobalBounds().top;
	this->setY(this->getY() + distance);
	this->setVY(0);
}


//bottom collision logic
void GameObject::collideBottom(GameObject* o)
{
	int distance = animation.getSprite()->getGlobalBounds().top + animation.getSprite()->getGlobalBounds().height
		- o->getAnimation()->getSprite()->getGlobalBounds().top;
	this->grounded = true;
	this->setY(this->getY() - distance);
	this->setVY(0);
}

bool GameObject::isAccessible()
{
	return true;
}


//get the grounded variable
//postcondition: bool
bool GameObject::isGrounded() 
{
	return this->grounded;
}

void GameObject::setMoving(bool moving)
{
	this->moving = moving;
}

bool GameObject::isMoving()
{
	return moving;
}

void GameObject::setFlipped(bool flipped)
{
	int offset = -1;
	if (this->flipped == flipped) {
		return;//nothing to do
	}
	animation.getSprite()->scale(offset * 1, 1);
	this->flipped = flipped;
}

bool GameObject::isFlipped()
{
	return flipped;
}

void GameObject::setCoins(int coins)
{
	this->coins = coins;
}

void GameObject::addCoin()
{
	coins++;
}

int GameObject::getCoins()
{
	return coins;
}

void GameObject::setVectorPosition(int pos)
{
	vectorPosition = pos;
}

int GameObject::getVectorPosition()
{
	return vectorPosition;
}


//set the grounded variable
//precondition: bool
void GameObject::setGrounded(bool grounded)
{
	this->grounded = grounded;
}



