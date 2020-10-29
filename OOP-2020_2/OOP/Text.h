#pragma once
#include "GameObject.h"
class Text : public GameObject
{
	string massage;
public:
	Text(const Position& pos, const string& message, GameObject* parent);

	void update() override;
	void draw() override;
		
};

