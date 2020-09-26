#include "Block.h"
#include "InputManager.h"
#include "Screen.h"

Block::Block(int x, int y, const string & shape)
	: GameObject(x, y, shape)
{
}

void Block::update()
{
	Position pos = getPos();
	if (inputManager.getKeyDown(VK_LEFT) == true) {
		setPos(pos.x - 1, pos.y);
	}
	if (inputManager.getKeyDown(VK_RIGHT) == true) {
		setPos(pos.x + 1, pos.y);
	}
	if (inputManager.getKeyDown(VK_UP) == true) {
		setPos(pos.x, pos.y - 1);
	}
	if (inputManager.getKeyDown(VK_DOWN) == true) {
		setPos(pos.x, pos.y + 1);
	}
}

