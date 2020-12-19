#include "EndingScript.h"
#include "GameObject.h"
#include "GridScript.h"
#include "Screen.h"

EndingScript::EndingScript(GameObject * gameObject)
	:Component(gameObject)
{
}

void EndingScript::start()
{
	transform = getTransform();
}

void EndingScript::update()
{
}

void EndingScript::draw()
{
	if (GameObject::Find("Grid")->getComponent<GridScript>()->getOver()) {
		Position pos = transform->getPosition();
		Position size = transform->getSize();
		getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 2, size.y + 2 });
	}
}
