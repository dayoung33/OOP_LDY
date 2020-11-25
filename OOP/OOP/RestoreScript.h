#pragma once
#include "ClickableScript.h"
class RestoreScript : public ClickableScript
{
public:
	RestoreScript(GameObject* gameObject);

	void start() override;

	bool isMatching(GameObject* associated);
	void show();

protected:
	// ClickableScript을(를) 통해 상속됨
	virtual void onClick() override;
};

