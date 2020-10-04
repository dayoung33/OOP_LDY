#pragma once
#include "GameObject.h"
class Table;
class Block :
	public GameObject
{
public:
	Block(int x = 10, int y = 1, const string& shape = "бс");

	void update() override;
	bool checkCollision();
	void setActive(bool active_on);
	void setInactivePos(int y);
	int getInactivePos();
	bool getActive();
	void setFallPos(int y);
	void upSpeed(int level) { speed = level; }

private:
	int inactivePosY = 0;
	int fallPos;
	bool active = true;
	float delta = 0.0f;
	int speed = 1;
};

