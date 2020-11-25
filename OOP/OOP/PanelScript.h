#pragma once
#include "Component.h"

class GameObject;
class Transform;

class PanelScript : public Component {
	int count;
	Transform* transform;

public:
	PanelScript(GameObject* gameObject);
	void start() override;
	void update() override;
	void draw() override;
};

