#pragma once
#include "Component.h"
#include "Utils.h"
#include <string>
using namespace std;

class ClickableScript : public Component
{
	Position pos;
	Position size;

	bool isOverlapped(const Position& position, const Position& sz = Position{ 1,1 }) const;

public:
	ClickableScript(GameObject* gameObject);
	
	void start() override;
	void update() override;
	void draw() override;

protected:
	virtual void onLeftButtonClick() = 0;
	virtual void onRightButtonClick() = 0;
	void setPos(Position pos);
};

