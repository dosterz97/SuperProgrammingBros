#include "stdafx.h"
#include "Block.h"

#include <iostream>

using namespace std;
Block::Block()
{
}

Block::Block(int x, int y, Animation a) : GameObject(x, y, a)
{
	GameObject(x, y, a);
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
}