#include "ClickableScript.h"
#include "InputManager.h"
#include "Transform.h"
#include "Screen.h"

ClickableScript::ClickableScript(GameObject * gameObject)
	:Component(gameObject)
{
}

void ClickableScript::start()
{
	size = getTransform()->getSize();
	pos = Position{ getTransform()->getPosition().x +size.x,getTransform()->getPosition().y };
}

void ClickableScript::update()
{
	if (getInputManager().GetLeftMouseDown()) {
		if (isOverlapped(getInputManager().mousePosition)) {
			onClick();
		}
	}
}

void ClickableScript::draw()
{
	getScreen().drawRectangle(Position{ pos.x + 1, pos.y - 1 }, Position{ 5, 2 });
	getScreen().draw(Position{ pos.x +4 , pos.y }, "-");
}

void ClickableScript::setPos(Position pos)
{
	this->pos = pos;
}

bool ClickableScript::isOverlapped(const Position & position, const Position & sz) const
{
	Position pos = getTransform()->getPosition();
	return (pos.x + size.x <= position.x && position.x < pos.x + size.x + 5)
		&& (pos.y <= position.y && position.y < pos.y + size.y);
	
}
