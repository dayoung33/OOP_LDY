#pragma once
#include "GameObject.h"
class TextInput : public GameObject
{
	int value;

public:
	TextInput(const Position& pos, int data, GameObject* parent);

	void update() override;
	void draw() override;

	void setValue(int value) { this->value = value; }

};

