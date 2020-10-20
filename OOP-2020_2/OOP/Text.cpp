#include "Text.h"
#include "InputManager.h"

Text::Text(const Position & pos, const string & message, GameObject * parent)
	: GameObject(pos, message.c_str(), parent)
{
}

void Text::update()
{
	Position pos = getPos();
	//if (inputManager.GetLeftMouseDown()) setPos(pos + Position::left);
	//if (inputManager.GetRightMouseDown()) setPos(pos + Position::right);
}
