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
	// ClickableScript을(를) 통해 상속됨
	virtual void onClick() override;
};

