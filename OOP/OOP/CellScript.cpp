#include "CellScript.h"
#include "Transform.h"
CellScript::CellScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet), m_flag(0)
{
}

void CellScript::start()
{
	transform = getTransform();
	transform->setShape(to_string(m_flag));
}


void CellScript::onLeftButtonClick()
{
	transform->setShape(to_string(m_flag));
	if (m_flag == 0)
		transform->setShape(" ");
	if(m_flag==9)
		transform->setShape("@");
}

void CellScript::onRightButtonClick()
{
	transform->setShape("/");
}


