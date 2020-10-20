#pragma once
#include "GameObject.h"
class Text : public GameObject
{
public:
	Text(const Position& pos, const string& message, GameObject* parent);

	void update() override;
		
};

