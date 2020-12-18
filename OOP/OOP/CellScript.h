#pragma once
#include "ClickableScript.h"
class CellScript : public ClickableScript
{
	Transform* transform;
	int m_flag;
public:
	CellScript(GameObject* gameObjcet);

	void start() override;

	void setFlag(int flag) { m_flag = flag; }
	int getFlag() { return m_flag; }
protected:
	// ClickableScript��(��) ���� ��ӵ�
	virtual void onLeftButtonClick() override;
	virtual void onRightButtonClick() override;
};

