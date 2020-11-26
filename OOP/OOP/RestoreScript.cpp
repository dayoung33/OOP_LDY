#include "RestoreScript.h"
#include "GameObject.h"
#include "Screen.h"

RestoreScript::RestoreScript(GameObject * gameObject)
	:ClickableScript(gameObject),associated(nullptr)
{
}

void RestoreScript::start()
{
	gameObject->setHiddenflag(true);
}

void RestoreScript::draw()
{
	Position pos = getTransform()->getPosition();
	Position size = getTransform()->getSize();
	getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, size);
	getScreen().draw(Position{ pos.x + 1, pos.y }, gameObject->getName().c_str());
}


void RestoreScript::setObject(GameObject * associated)
{
	this->associated = associated;
}

void RestoreScript::onClick()
{
	if (associated == nullptr) return;
	associated->setHiddenflag(false);
	gameObject->setHiddenflag(true);
}

bool RestoreScript::isMatching(GameObject * associated)
{
	return associated == this->associated;
}

