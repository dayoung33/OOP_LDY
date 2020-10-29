#include "Block.h"
#include "InputManager.h"
#include "Screen.h"
#include "Panel.h"
#include "GameTable.h"

enum eState { EMPTY, BLOCK, WALL };

Block::Block(const Position & pos, const string & shape, const Position & size, GameObject * parent, bool rotatable)
	: GameObject(pos, shape, parent), size(size), internalShapeData(new char[size.x*size.y + 1]), rotatable(rotatable), pause(false)
{
	fallPos = 0;
	Gametable = 0;
	delta = 0.0f;
	speed = 1;
}

Block::~Block()
{
	if (internalShapeData != nullptr)
		delete[] internalShapeData;
}

void Block::update()
{
	Position pos = getPos();
	int cnt = 0;
	if (rotatable && !pause) {
		if (pos.y + size.y > dynamic_cast<Panel*>(parent)->getHeight()) {
			rotatable = false;
			return;
		}
		delta += (0.1f * speed);
		if (delta > 1.f) {
			setPos(pos + Position::down);
			delta = 0.f;
		}

		if (inputManager.getKeyDown(VK_UP))
			rotateShape(); //xxoxoxox
		if (checkBottomCollision()&&inputManager.getKeyDown(VK_DOWN))
			setPos(pos + Position::down);
		if ( checkLeftCollision()&& inputManager.getKeyDown(VK_LEFT)) 
			setPos(pos + Position::left);
		if (checkRightCollision() && inputManager.getKeyDown(VK_RIGHT)) 
			setPos(pos + Position::right);
		if (inputManager.getKeyDown(VK_SPACE))
		{
			while (1)
			{
				if (!setFallPos(cnt))
				{
					setPos(getPos().x, getPos().y + cnt);
					rotatable = false;
					break;
				}
				cnt++;
			}
		}
	}
}

void Block::draw()
{
	Position pos = getWorldPos();
	screen.drawShape(pos, size, getShape());
}

bool Block::setFallPos(int y)
{
	Position pos = Position{ getPos().x,getPos().y + y };
	Position checkPos;
	auto gt = dynamic_cast<GameTable*>(Gametable);

	const char* shape = getShape();

	for (int h = size.y - 1; h >= 0; h--) //하단부터 검사
	{
		for (int w = 0; w < size.x; w++)
		{
			if (shape[h*size.x + w] != ' ') {
				checkPos = Position{ pos.x + w ,pos.y + h };
				if (checkPos.y == dynamic_cast<Panel*>(parent)->getHeight()) 
					return false;
				if (gt->getState(checkPos.x, checkPos.y + 1) == BLOCK)				
					return false;			
				else 
					continue;
			}
		}
	}
	return true;
}

bool Block::checkBottomCollision()
{
	Position pos = getPos();
	Position checkPos;
	auto gt = dynamic_cast<GameTable*>(Gametable);

	const char* shape = getShape();

	for (int h = size.y - 1; h >= 0; h--) //하단부터 검사
	{
		for (int w = 0; w < size.x; w++)
		{
			if (shape[h*size.x + w] != ' ') {
				checkPos = Position{ pos.x + w ,pos.y + h };
				if (checkPos.y  == dynamic_cast<Panel*>(parent)->getHeight()) {
					rotatable = false;
					return false;
				}					
				if (gt->getState(checkPos.x, checkPos.y+1) == BLOCK)
				{					
					rotatable = false;
					return false;
				}					
				else {
					continue;
				}
			}
		}
	}
	return true;
}

bool Block::checkRightCollision()
{
	Position pos = getPos();
	Position checkPos;
	auto gt = dynamic_cast<GameTable*>(Gametable);

	const char* shape = getShape();

	for (int w = size.x-1; w >= 0; w--)
	{
		for (int h = 0; h < size.y; h++) 
		{
			if (shape[h*size.x + w] != ' ') {
				checkPos = Position{ pos.x + w ,pos.y + h };
				if (checkPos.x == dynamic_cast<Panel*>(parent)->getWidth())
					return false;

				if (gt->getState(checkPos.x + 1, checkPos.y) == BLOCK)
					return false;
				else
					continue;
			}
		}
	}
	return true;
}

bool Block::checkLeftCollision()
{
	Position pos = getPos();
	Position checkPos;
	auto gt = dynamic_cast<GameTable*>(Gametable);

	const char* shape = getShape();

	for (int w = 0; w < size.x; w++)
	{
		for (int h = 0; h < size.y; h++)
		{
			if (shape[h*size.x + w] != ' ') {
				checkPos = Position{ pos.x + w ,pos.y + h };
				if (checkPos.x == 0) 
					return false;
				if (gt->getState(checkPos.x - 1, checkPos.y) == BLOCK)	
					return false;
				else 
					continue;	
			}
		}
	}
	return true;
}

void Block::rotateShape()
{
	string shape = getShape();
	int w = size.x; int h = size.y;
	const char* p = shape.c_str();
	strncpy(internalShapeData, p, w*h);
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			internalShapeData[(w - 1 - x)*h + y] = p[y*w + x];
	setShape(internalShapeData);
	size.x = h; size.y = w;
}

