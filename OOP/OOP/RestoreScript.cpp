#include "RestoreScript.h"
#include "GameObject.h"
#include "Screen.h"

RestoreScript::RestoreScript(GameObject * gameObject)
	:ClickableScript(gameObject)
{
}

void RestoreScript::start()
{
	setHiddenflag(true);
	restores.push_back(this);
	this->setPos(Position{ (getScreen().getWidth() - 9), (getScreen().getHeight() - 2) });
}

void RestoreScript::show()
{
	setHiddenflag(false);
	int numberOfRestoreButtons = 0;
	for (auto obj : restores) {
		auto restoreButton = dynamic_cast<RestoreScript *>(obj);
		if (restoreButton == nullptr) continue;
		if (restoreButton->getHiddenflag() == false) numberOfRestoreButtons++;
	}
	this->setPos(Position{ (getScreen().getWidth() - 9), (getScreen().getHeight() - 2 - (numberOfRestoreButtons*2))});
	//getScreen().drawRectangle(Position{ (getScreen().getWidth() - 9), (getScreen().getHeight() - 2 - (numberOfRestoreButtons * 2)) }, Position{ 5, 2 });
}

void RestoreScript::onClick()
{
	if (gameObject == nullptr) return;
	gameObject->setHiddenflag(false);
	setHiddenflag(true);
}

bool RestoreScript::isMatching(GameObject * associated)
{
	return associated == gameObject;
}