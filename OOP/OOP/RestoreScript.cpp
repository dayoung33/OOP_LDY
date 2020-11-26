#include "RestoreScript.h"
#include "GameObject.h"
#include "Screen.h"

RestoreScript::RestoreScript(GameObject * gameObject)
	:ClickableScript(gameObject)
{
}

void RestoreScript::start()
{
	//setHiddenflag(true);
}

void RestoreScript::draw()
{
	Position pos = getTransform()->getPosition();
	Position size = getTransform()->getSize();
	getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 2, size.y + 2 });
	getScreen().draw(Position{ pos.x + 1, pos.y + 1 }, gameObject->getName().c_str());
}

void RestoreScript::show()
{
	//gameObject->setHiddenflag(false);
	//int numberOfRestoreButtons = 0;
	//for (auto obj : restores) {
	//	auto restoreButton = dynamic_cast<RestoreScript *>(obj);
	//	if (restoreButton == nullptr) continue;
	//	if (restoreButton->getHiddenflag() == false) numberOfRestoreButtons++;
	//}
	//this->setPos(Position{ (getScreen().getWidth() - 9), (getScreen().getHeight() - 2 - (numberOfRestoreButtons*2))});
}

void RestoreScript::onClick()
{
	if (gameObject == nullptr) return;
	gameObject->setHiddenflag(true);
}

bool RestoreScript::isMatching(GameObject * associated)
{
	return associated == gameObject;
}