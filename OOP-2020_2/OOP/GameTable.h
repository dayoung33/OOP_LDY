#pragma once
#include <vector>
using namespace std;

#include "GameObject.h"
class GameTable : public GameObject
{
	int width;
	int height;
	string title;
	vector<vector<int>> table;

	int score = 0;
	bool gameover;


public:
	GameTable(const Position& pos, int width, int height,GameObject* parent);

	int getHeight() { return height; }
	int getWidth() { return width; }

	void update() override;
	void draw() override;

	void addBlock(int x, int y);
	void deleteLine(int y);
	int getState(int x, int y);
	bool getOver() { return gameover; }
	void restart();
};

