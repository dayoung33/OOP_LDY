#pragma once
#include "ClickableScript.h"
class ExitScript :public ClickableScript
{
public:
	ExitScript(GameObject* gameObjcet);

	void draw() override;

	// ClickableScript을(를) 통해 상속됨
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

