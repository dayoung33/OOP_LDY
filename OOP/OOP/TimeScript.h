#pragma once
#include "Component.h"
class TimeScript : public Component
{
	float deltaTime;
	Transform* transform;

public:
	TimeScript(GameObject* gameObject);
	void start() override;
	void update() override;
	void draw() override;
	void reset();
};

