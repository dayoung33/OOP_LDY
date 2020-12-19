#include "ExitScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "GridScript.h"
#include "Screen.h"

ExitScript::ExitScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet)
{
}

void ExitScript::draw()
{
	if (GameObject::Find("Grid")->getComponent<GridScript>()->getOver()) {
		Position pos = getTransform()->getPosition();
		Position size = getTransform()->getSize();
		getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 2, size.y + 2 });
		getScreen().draw(Position{ pos.x + 3, pos.y +1 }, "EXIT");
	}
}

void ExitScript::onLeftButtonClick()
{
	exit(0);
}

void ExitScript::onRightButtonClick()
{
}
