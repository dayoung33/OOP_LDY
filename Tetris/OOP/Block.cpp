#include "Block.h"
#include "InputManager.h"
#include "Screen.h"
//#include "Utils.h"


Block::Block(int x, int y, const string & shape)
	: GameObject(x, y, shape)
{
}

void Block::update()
{
	Position pos = getPos();
	delta += (0.01f * speed);
	if (delta > 1.f) {
		setPos(pos.x, pos.y + 1);
		delta = 0.f;
	}

	//Borland::gotoxy(40, 10);
	//printf("x : %d, y : %d ", pos.x, pos.y);

	if (inputManager.getKeyDown(VK_LEFT) == true&& pos.x > 2) {
		setPos(pos.x - 2, pos.y);
	}
	if (inputManager.getKeyDown(VK_RIGHT) == true&& pos.x < screen.getWidth()-4) {
		setPos(pos.x + 2, pos.y);
	}
	if (inputManager.getKeyDown(VK_DOWN) == true&& pos.y < screen.getHeight()-2) {
		setPos(pos.x, pos.y + 1);
	}
	//if (inputManager.getKeyDown(VK_SPACE) == true) {
		
	//}


}


