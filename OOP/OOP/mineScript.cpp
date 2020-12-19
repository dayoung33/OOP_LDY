#include "mineScript.h"
#include "GameObject.h"
#include "GridScript.h"
#include "Screen.h"


mineScript::mineScript(GameObject * gameObject)
	:Component(gameObject),m_founded(-1),m_mine(0)
{
}

void mineScript::start()
{
	transform = getTransform();
	m_mine = GameObject::Find("Grid")->getComponent<GridScript>()->getMineCnt();
}

void mineScript::update()
{
	m_founded = GameObject::Find("Grid")->getComponent<GridScript>()->getFound();
}

void mineScript::draw()
{
	Position pos = transform->getPosition();
	string temp = to_string(m_founded) + " / " + to_string(m_mine);
	getScreen().draw(Position{ pos.x , pos.y },temp.c_str());
}
