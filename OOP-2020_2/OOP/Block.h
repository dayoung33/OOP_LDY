#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
	Position size;
	char* internalShapeData; // it is used only in rotateShape().
	bool rotatable;
	float delta;
	int speed;

public:
	Block(const Position& pos, const string& shape, const Position& size, GameObject* parent = nullptr, bool rotatable = true);
	~Block();

	void update() override;
	void draw() override;
	void setRotatable(bool rotate) { rotatable = rotate; }
	Position getSize() { return size; }
	
private:
	void rotateShape();


};

