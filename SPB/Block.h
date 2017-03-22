#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
public:
	Block();
	Block(int x,int y,Animation a,int frame);

	void foo();
	void collideBottom(GameObject*);
	~Block();

private: 
};

