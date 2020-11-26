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
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onClick() override;
};

