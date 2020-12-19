#pragma once
#include "Component.h"
class mineScript : public Component
{
	int m_founded;
	int m_mine;
	Transform* transform;

public:
	mineScript(GameObject* gameObject);
	void start() override;
	void update() override;
	void draw() override;
};

