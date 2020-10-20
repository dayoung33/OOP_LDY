#include "GameObject.h"
#include "Screen.h"
#include "InputManager.h"

GameObject::GameObject(int x, int y, const string& shape, GameObject* parent = nullptr)
	: shape(shape), screen(*Screen::getInstance()),
	inputManager(*InputManager::getInstance()),
	pos(x, y), parent(parent), dirty(false)
{
	setParentPos(parent ? parent->getWorldPos() : Position::zeros);
	if (parent) parent->add(this);

	start();
}
GameObject::GameObject(const Position& pos, const string& shape, GameObject* parent = nullptr)
	: GameObject(pos.x, pos.y, shape, parent) {}

void GameObject::add(GameObject * child)
{
	if (!child) return;
	children.push_back(child);
}

void GameObject::setPos(int x, int y)
{
	pos.x = x; pos.y = y;
}

void GameObject::setPos(const Position & pos)
{
	this->pos.x = pos.x; this->pos.y = pos.y;
	dirty = true;
}

void GameObject::setParent(GameObject * parent)
{
	this->parent = parent;
	setParentPos(parent ? parent->getWorldPos() : Position::zeros);
	for (auto child : children) child->internalUpdatePos(true);
}

void GameObject::internalUpdatePos(bool dirty)
{
	bool inheritedDirty = dirty;
	if (inheritedDirty == false) {
		if (this->dirty == true) inheritedDirty = true;
	}
	else {
		if (parent) setParentPos(parent->getWorldPos());
	}

	for (auto child : children) child->internalUpdatePos(inheritedDirty);
	this->dirty = false;
}

void GameObject::internalUpdate()
{
	update();
	for (auto child : children) child->internalUpdate();
}

void GameObject::internalDraw()
{
	draw();
	for (auto child : children) child->internalDraw();
}

void GameObject::draw()
{
	screen.draw(getWorldPos(), shape.c_str());
}

