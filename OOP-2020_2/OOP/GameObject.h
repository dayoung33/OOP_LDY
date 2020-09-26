#pragma once
#include <string>
using namespace std;

#include "Utils.h"

class Screen;
class InputManager;

class GameObject
{
	string shape;
	Position pos;

protected:
	Screen& screen;
	InputManager& inputManager;

public:
	GameObject(int x, int y, const string& shape);
	virtual ~GameObject() {}

	void setPos(int x, int y) { pos.x = x; pos.y = y; }
	void setPos(const Position& pos) { this->pos.x = pos.x; this->pos.y = pos.y; }
	Position getPos() const { return pos; }

	virtual void update() {}
	virtual void start() {}
	virtual void draw();
};

