#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
	GameObject* Gametable;
	Position size;
	char* internalShapeData; // it is used only in rotateShape().
	bool rotatable;
	bool pause;
	Position fallPos;
	float delta;
	int speed;

public:
	Block(const Position& pos, const string& shape, const Position& size, GameObject* parent = nullptr, bool rotatable = true);
	~Block();

	void update() override;
	void draw() override;
	bool setFallPos(int y);
	void setRotatable(bool rotate) { rotatable = rotate; }
	bool getRotatable() { return rotatable; }
	void setPause(bool _pause) { pause = _pause; }
	bool getPause() { return pause; }
	Position getSize() { return size; }
	void setGametable(GameObject* gametable) { Gametable = gametable; }
	bool checkBottomCollision();
	bool checkRightCollision();
	bool checkLeftCollision();
	
private:
	void rotateShape();


};

