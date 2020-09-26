#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
public:
	Block(int x = 5, int y = 5, const string& shape = "(^_^)");

	void update() override;

};

