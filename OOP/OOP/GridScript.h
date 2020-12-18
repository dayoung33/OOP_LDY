#pragma once
#include "Component.h"
#include <vector>
using namespace std;

class GridScript :
	public Component
{
	Transform* transform;
	vector<GameObject*> cells;
	bool m_isGameOver;
	int m_mineCnt;
	int m_foundMine;
	int m_width;
	int m_height;
public:
	GridScript(GameObject* gameObject);
	void start() override;
	void update() override;

private:
	void SetMine();
	int MineNumCheck(int index);
};

