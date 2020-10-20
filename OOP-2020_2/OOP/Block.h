#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
	Position size;

public:
	Block(const Position& pos, const string& shape, const Position& size, GameObject* parent = nullptr);

	void update() override;
	void draw() override;

};

