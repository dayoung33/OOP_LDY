#pragma once
#include <vector>
using namespace std;
#include "Utils.h"

class Screen;
class InputManager;
class Block;

class Table 
{
	Table();
public:
	static Table* getInstance()
	{
		if (!instance)
			instance = new Table;

		return instance;
	}
	~Table();

public:
	void update();
	void start();
	void draw();

public:
	int getCombo() { return combo; }
	int getLevel() { return level; }
	int getScore() { return score; }


private:
	static Table* instance;
	Screen& screen;
	InputManager& inputManager;

	Block* block;
	int m_tableWidth;
	int m_tableHeight;

	vector<vector<int>> table;

	int score = 0;
	int combo = 0;
	int level = 1;
};

