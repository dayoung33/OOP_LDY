#include "MinimizeScript.h"
#include "GameObject.h"
#include "RestoreScript.h"
#include "Screen.h"

MinimizeScript::MinimizeScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet), restore(nullptr)
{
	
}
void MinimizeScript::draw()
{
	Position size = getTransform()->getSize();
	Position pos = getTransform()->getPosition();
	getScreen().drawRectangle(Position{ pos.x , pos.y }, size);
	getScreen().draw(Position{ pos.x + 2 , pos.y+1 }, "-");
}

void MinimizeScript::setRestore(GameObject * restore)
{
	this->restore = restore;
}

void MinimizeScript::onClick()
{
	if (gameObject == nullptr) return;
	gameObject->getParent()->setHiddenflag(true);
	restore->setHiddenflag(false);

}
