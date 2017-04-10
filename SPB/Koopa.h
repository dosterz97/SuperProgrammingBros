#pragma once
#include "GameObject.h"
class Koopa :
	public GameObject
{
public:
	Koopa();
	Koopa(int x, int y, Animation a, int frame, Animation shell);

	void foo();
	void collideTop(GameObject*);
	~Koopa();

private:
	Animation shellAnimation;
};

