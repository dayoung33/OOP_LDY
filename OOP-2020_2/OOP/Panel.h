#pragma once
#include "GameObject.h"
class Panel : public GameObject
{
	int width;
	int height;
	string title;

public:
	Panel(const string& title, const Position& pos, int width, int height, GameObject* parent);

	void update() override;
	void draw() override;

};

