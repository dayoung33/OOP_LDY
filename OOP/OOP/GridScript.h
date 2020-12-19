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
	bool m_startFlag;
	int m_mineCnt;
	int m_foundMine;
	int m_width;
	int m_height;
	bool m_isEndInit;
public:
	GridScript(GameObject* gameObject);
	void start() override;
	void update() override;
	void Bomb(int x, int y);
	int getFound() { return m_foundMine; }
	void setFound() {  m_foundMine++; }
	int getMineCnt() { return m_mineCnt; }
	int getOver() { return m_isGameOver; }
	void GameOver() { m_isGameOver = true; }
	bool GetStart() { return m_startFlag; }
	void GameStart() { m_startFlag = true; }
	void reset();
private:
	void SetMine();
	int MineNumCheck(int index);
	bool CheckPos(int x, int y);
	void DoubleCheck(int x, int y);
	void TripleCheck(int x, int y);
	void QuadCheck(int x, int y);
};

