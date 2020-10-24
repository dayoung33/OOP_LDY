#include "Block.h"
#include "InputManager.h"
#include "Screen.h"
#include "Panel.h"


Block::Block(const Position & pos, const string & shape, const Position & size, GameObject * parent, bool rotatable)
	: GameObject(pos, shape, parent), size(size), internalShapeData(new char[size.x*size.y + 1]), rotatable(rotatable)
{
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
	if (rotatable) {
		Position pos = getPos();
		delta += (0.1f * speed);
		if (delta > 1.f) {
			setPos(pos + Position::down);
			delta = 0.f;
		}

		if (inputManager.getKeyDown(VK_UP))
			rotateShape(); //xxoxoxox
		if (inputManager.getKeyDown(VK_DOWN)&& pos.y <  dynamic_cast<Panel*>(parent)->getHeight()- size.y +1 )
			setPos(pos + Position::down);
		if (inputManager.getKeyDown(VK_LEFT)&& pos.x > 0) 
			setPos(pos + Position::left);
		if (inputManager.getKeyDown(VK_RIGHT) && pos.x < dynamic_cast<Panel*>(parent)->getWidth() - size.x + 1) 
			setPos(pos + Position::right);
	}
}

void Block::draw()
{
	Position pos = getWorldPos();
	screen.drawShape(pos, size, getShape());
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

