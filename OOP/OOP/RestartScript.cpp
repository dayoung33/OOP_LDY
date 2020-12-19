#include "RestartScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "GridScript.h"
#include "TimeScript.h"
#include "Screen.h"

RestartScript::RestartScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet)
{
}

void RestartScript::draw()
{
	if (GameObject::Find("Grid")->getComponent<GridScript>()->getOver()) {
		Position pos = getTransform()->getPosition();
		Position size = getTransform()->getSize();
		getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 2, size.y + 2 });
		getScreen().draw(Position{ pos.x + 1, pos.y +1 }, "RESTART");

	}
}

void RestartScript::onLeftButtonClick()
{
	GameObject::Find("Grid")->getComponent<GridScript>()->reset();
	GameObject::Find("timeText")->getComponent<TimeScript>()->reset();
}

void RestartScript::onRightButtonClick()
{
}
