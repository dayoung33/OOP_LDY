#include "CellScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "GridScript.h"
#include "Screen.h"
CellScript::CellScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet), m_flag(0), isBomb(false), startFlag(false)
{
}

void CellScript::start()
{
	transform = getTransform();
}

void CellScript::draw()
{

	if (isBomb) {
		if (m_flag == 0)
			transform->setShape(" ");
		else if(m_flag <9)
			transform->setShape(to_string(m_flag));
		else
			transform->setShape("@");
	}
	Position pos = transform->getPosition();
	Position size = transform->getSize();
	string shape = transform->getShape();
	getScreen().drawShape(pos, size, shape.c_str());
	
}


void CellScript::reset()
{
	isBomb = false;
	startFlag = false;
	m_flag = 0;
	transform->setShape(to_string(m_flag));
}

void CellScript::onLeftButtonClick()
{
	if (!gameObject->getParent()->getComponent<GridScript>()->getOver()) {
		if (!startFlag) {
			if (!gameObject->getParent()->getComponent<GridScript>()->GetStart())
				gameObject->getParent()->getComponent<GridScript>()->GameStart();
			startFlag = true;
		}
		transform->setShape(to_string(m_flag));
		if (m_flag == 0) {
			//transform->setShape(" ");
			gameObject->getParent()->getComponent<GridScript>()->Bomb(transform->getPosition().x, transform->getPosition().y);
		}
		if (m_flag == 9) {
			transform->setShape("@");
			gameObject->getParent()->getComponent<GridScript>()->GameOver();
		}
	}
}

void CellScript::onRightButtonClick()
{
	if (!gameObject->getParent()->getComponent<GridScript>()->getOver()) {
		transform->setShape("/");
		if (m_flag == 9)
			gameObject->getParent()->getComponent<GridScript>()->setFound();
	}
}


