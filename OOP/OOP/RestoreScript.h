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
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onClick() override;
};

