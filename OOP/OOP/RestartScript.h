#pragma once
#include "ClickableScript.h"
class RestartScript : public ClickableScript
{
public:
	RestartScript(GameObject* gameObjcet);

	void draw() override;
private:
	// ClickableScript을(를) 통해 상속됨
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

