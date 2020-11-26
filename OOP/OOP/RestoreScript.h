#pragma once
#include "ClickableScript.h"
class RestoreScript : public ClickableScript
{
	GameObject* associated;
public:
	RestoreScript(GameObject* gameObject);

	void start() override;
	void draw() override;

	bool isMatching(GameObject* associated);
	void setObject(GameObject* associated);

protected:
	// ClickableScript을(를) 통해 상속됨
	virtual void onClick() override;
};

