#include "stdafx.h"
#include "Koopa.h"

#include <iostream>

using namespace std;
Koopa::Koopa()
{
}

Koopa::Koopa(int x, int y, Animation a, int frame, Animation shell) : GameObject(x, y, a, frame)
{
	GameObject(x, y, a, frame);
	this->shellAnimation = shell;
}


Koopa::~Koopa()
{
}


void Koopa::foo()
{
	cout << "foo u polymorphism" << endl;
}

void Koopa::collideTop(GameObject* o) {
	if (o->getTeam() == 1) {
		if (this->getAnimation()->getName() == "koopa") {
			this->setAnimation(shellAnimation);
		}
		else {
			this->setToDie();
		}
	}
}