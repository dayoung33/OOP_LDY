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
}

void ClickableScript::update()
{
	if (getInputManager().GetLeftMouseDown()) {
		if (isOverlapped(getInputManager().mousePosition)) {
			onLeftButtonClick();
		}
	}
	if (getInputManager().GetRightMouseDown()) {
		if (isOverlapped(getInputManager().mousePosition)) {
			onRightButtonClick();
		}
	}
}

void ClickableScript::draw()
{
}

void ClickableScript::setPos(Position pos)
{
	this->pos = pos;
}

bool ClickableScript::isOverlapped(const Position & position, const Position & sz) const
{
	Position pos = getTransform()->getPosition();
	Position size = getTransform()->getSize();
	return (pos.x <= position.x && position.x < pos.x + size.x)
		&& (pos.y <= position.y && position.y < pos.y + size.y);
	
}
