#pragma once
#include "ClickableScript.h"
class CellScript : public ClickableScript
{
	Transform* transform;
	int m_flag;
	bool isBomb;
	bool startFlag;
public:
	CellScript(GameObject* gameObjcet);

	void start() override;
	void draw() override;

	void setFlag(int flag) { m_flag = flag; }
	int getFlag() { return m_flag; }

	void OnBomb() { isBomb = true; }
	bool getIsBomb() { return isBomb; }

	void reset();
protected:
	// ClickableScript을(를) 통해 상속됨
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

