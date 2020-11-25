#pragma once
class GameObject;
class Transform;
class InputManager;
class Screen;

class Component
{
	bool		hideFlag;
protected:

	GameObject* gameObject;
	
public:
	Component(GameObject* gameObject);

	Transform* getTransform() const;
	InputManager& getInputManager() const;
	Screen& getScreen() const;
	void setHiddenflag(bool flag);
	bool getHiddenflag() { return hideFlag; }

	virtual void start() {}
	virtual void update() {}
	virtual void draw() {}
};

