#pragma once
#include "ClickableScript.h"
class MinimizeScript : public ClickableScript
{
	GameObject* restore;
public:
	MinimizeScript(GameObject* gameObjcet);

	void draw() override;
	void setRestore(GameObject* restore);
protected:
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onClick() override;
};

