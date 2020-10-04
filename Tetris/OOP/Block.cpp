#include "Block.h"
#include "InputManager.h"
#include "Screen.h"
#include "Table.h"
//#include "Utils.h"


Block::Block(int x, int y, const string & shape)
	: GameObject(x, y, shape), fallPos(screen.getHeight() - 3)
{
}

void Block::update()
{
	Position pos = getPos();

	if (active) {
		delta += (0.02f * speed);
		if (delta > 1.f) {
			setPos(pos.x, pos.y + 1);
			delta = 0.f;
		}

		//Borland::gotoxy(40, 10);
		//printf("x : %d, y : %d ", pos.x, pos.y);

		if (inputManager.getKeyDown(VK_LEFT) == true && pos.x > 2) {
			setPos(pos.x - 2, pos.y);
		}
		if (inputManager.getKeyDown(VK_RIGHT) == true && pos.x < screen.getWidth() - 4) {
			setPos(pos.x + 2, pos.y);
		}
		if (inputManager.getKeyDown(VK_DOWN) == true && pos.y < screen.getHeight() - 2) {
			setPos(pos.x, pos.y + 1);
		}
		
		if (inputManager.getKeyDown(VK_SPACE) == true) {
			Table* table = Table::getInstance();
			if(table != nullptr)
				setPos(pos.x, table->getFallPos(pos.x));
		}
	}
}

bool Block::checkCollision()
{
	Position pos = getPos();

	return false;
}

void Block::setActive(bool active_on)
{
	active = active_on;
}

void Block::setInactivePos(int y)
{
	inactivePosY = y;
}

int Block::getInactivePos()
{
	return inactivePosY;
}

bool Block::getActive()
{
	return active;
}

void Block::setFallPos(int y)
{
	fallPos = y;
}


