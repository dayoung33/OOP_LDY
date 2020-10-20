#pragma once
#include <string>
#include <vector>

using namespace std;

#include "Utils.h"

class Screen;
class InputManager;

class GameObject
{
	string shape;
	Position pos;

	Position parentPos; // your parent's global position in space
	bool dirty; // mark it TRUE if your local position is changed.

protected:
	Screen& screen;
	InputManager& inputManager;

	vector<GameObject *> children;
	GameObject* parent;

	void setParentPos(const Position& parentPos) { this->parentPos = parentPos; }

public:
	GameObject(int x, int y, const string & shape, GameObject * parent);
	GameObject(const Position & pos, const string & shape, GameObject * parent);
	virtual ~GameObject() {}

	void add(GameObject* child);

	void setPos(int x, int y);
	void setPos(const Position& pos);

	Position getPos() const { return pos; }
	Position getWorldPos() const { return parentPos + pos; }

	const char* getShape() const { return shape.c_str(); }

	void setParent(GameObject* parent);
	
	virtual void start() {}

	void internalUpdatePos(bool dirty = false);
	void internalUpdate();
	void internalDraw();

	virtual void update() {}	
	virtual void draw();
};

