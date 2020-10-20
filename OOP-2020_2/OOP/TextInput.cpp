#include "TextInput.h"
#include "Screen.h"

TextInput::TextInput(const Position & pos, int data, GameObject * parent)
	: GameObject(pos, "", parent), value(data)
{
}

void TextInput::update()
{
	Position pos = getPos();
	//if (inputManager.GetLeftMouseDown()) setPos(pos + Position::left);
	//if (inputManager.GetRightMouseDown()) setPos(pos + Position::right);
}

void TextInput::draw()
{
	static char buffer[10];
	sprintf(buffer, "%3d\0", value);
	Position pos = getWorldPos();
	screen.draw(pos, buffer);
}
