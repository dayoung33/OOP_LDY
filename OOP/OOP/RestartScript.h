#pragma once
#include "ClickableScript.h"
class RestartScript : public ClickableScript
{
public:
	RestartScript(GameObject* gameObjcet);

	void draw() override;
private:
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

