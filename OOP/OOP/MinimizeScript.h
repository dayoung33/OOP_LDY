#pragma once
#include "ClickableScript.h"
class MinimizeScript : public ClickableScript
{
public:
	MinimizeScript(GameObject* gameObjcet);

protected:
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onClick() override;
};

