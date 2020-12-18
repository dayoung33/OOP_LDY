#include <iostream>
#include "Utils.h"
#include "GameObject.h"
#include "PanelScript.h"
#include "Screen.h"

using namespace std;

PanelScript::PanelScript(GameObject* gameObject)
	: Component(gameObject), count(0)
{}

void PanelScript::start() {
	transform = getTransform();
}

void PanelScript::update() {
	Position pos = transform->getPosition();
	Position size = transform->getSize();
	getScreen().drawRectangle(Position{ pos.x - 1, pos.y - 1 }, Position{ size.x + 2, size.y + 2 });
	getScreen().draw(Position{ pos.x + 1, pos.y - 1 }, gameObject->getName().c_str());
}