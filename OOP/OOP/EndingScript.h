#pragma once
#include "Component.h"
class EndingScript : public Component
{
	Transform* transform;

public:
	EndingScript(GameObject* gameObject);
	void start() override;
	void update() override;
	void draw() override;
};

