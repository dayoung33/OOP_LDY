#include "Panel.h"
#include "Screen.h"
#include "InputManager.h"

Panel::Panel(const string & title, const Position & pos, int width, int height, GameObject * parent)
	: GameObject(pos, "", parent),
	width(width), height(height), title(title)
{}

void Panel::update()
{
	Position pos = getPos();
}

void Panel::draw()
{
	Position pos = getWorldPos();
	screen.drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ width + 2, height + 2 });
	screen.draw(Position{ pos.x + 1, pos.y - 1 }, title.c_str());
}
