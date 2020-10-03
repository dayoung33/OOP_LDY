#include "GameObject.h"
#include "Screen.h"
#include "InputManager.h"

GameObject::GameObject(int x, int y, const string & shape)
	: shape(shape), screen(*Screen::getInstance()),
	inputManager(*InputManager::getInstance()),
	pos(x, y)
{
	start();
}

void GameObject::draw()
{
	screen.draw(pos.x, pos.y, shape.c_str());
}

