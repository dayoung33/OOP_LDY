#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
public:
	Block(int x = 10, int y = 2, const string& shape = "бс");

	void update() override;


private:
	float delta = 0.0f;
	int speed = 1;
};

