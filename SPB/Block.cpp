#include "stdafx.h"
#include "Block.h"

#include <iostream>

using namespace std;
Block::Block()
{
}

Block::Block(int x, int y, Animation a, int frame) : GameObject(x, y, a,frame)
{
	GameObject(x, y, a,frame);
}


Block::~Block()
{
}


void Block::foo()
{
	cout << "foo u polymorphism" << endl;
}

void Block::collideBottom(GameObject* o) {
	if (!this->isMoving()) {
		this->setVY(-3);
		this->setMoving(true);
	}
	if (getCoins() < 2) {
		
	}
}