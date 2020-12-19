#include "TimeScript.h"
#include "GameObject.h"
#include "GridScript.h"
#include "Screen.h"

TimeScript::TimeScript(GameObject * gameObject)
	:Component(gameObject), deltaTime(0.0f)
{
}

void TimeScript::start()
{
	transform = getTransform();
}

void TimeScript::update()
{
	if (GameObject::Find("Grid")->getComponent<GridScript>()->GetStart()
		&& !GameObject::Find("Grid")->getComponent<GridScript>()->getOver())
		deltaTime += 0.1f;
}

void TimeScript::draw()
{
	Position pos = transform->getPosition();
	string temp = to_string(deltaTime);
	getScreen().draw(Position{ pos.x , pos.y }, temp.c_str());
}

void TimeScript::reset()
{
	deltaTime = 0.0f;
}
