#pragma once
#include "ClickableScript.h"
class MinimizeScript : public ClickableScript
{
public:
	MinimizeScript(GameObject* gameObjcet);

protected:
	// ClickableScript을(를) 통해 상속됨
	virtual void onClick() override;
};

