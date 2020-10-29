#include "Text.h"
#include "InputManager.h"
#include "Screen.h"

Text::Text(const Position & pos, const string & message, GameObject * parent)
	: GameObject(pos, message.c_str(), parent), massage(message)
{
}

void Text::update()
{
	Position pos = getPos();
	//if (inputManager.GetLeftMouseDown()) setPos(pos + Position::left);
	//if (inputManager.GetRightMouseDown()) setPos(pos + Position::right);
}

void Text::draw()
{
	Position pos = getWorldPos();
	screen.draw(pos, massage.c_str());
}
