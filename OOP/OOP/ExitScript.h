#pragma once
#include "ClickableScript.h"
class ExitScript :public ClickableScript
{
public:
	ExitScript(GameObject* gameObjcet);

	void draw() override;

	// ClickableScript��(��) ���� ��ӵ�
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

