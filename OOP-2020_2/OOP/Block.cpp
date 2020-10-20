#include "Block.h"
#include "InputManager.h"
#include "Screen.h"


Block::Block(const Position & pos, const string & shape, const Position & size, GameObject * parent)
	: GameObject(pos, shape, parent), size(size) {}

void Block::update()
{
	Position pos = getPos();
	if (inputManager.getKeyDown(VK_DIVIDE)) setPos(pos + Position::left);
	if (inputManager.getKeyDown(VK_MULTIPLY)) setPos(pos + Position::right);
}

void Block::draw()
{
	Position pos = getWorldPos();
	screen.drawShape(pos, size, getShape());
}

