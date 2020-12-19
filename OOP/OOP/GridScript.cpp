#include "GridScript.h"
#include "GameObject.h"
#include "CellScript.h"
#include <time.h>

GridScript::GridScript(GameObject * gameObject)
	:Component(gameObject), 
	m_isGameOver(false),
	m_startFlag(false),
	m_isEndInit(false),
	m_mineCnt(16),
	m_foundMine(0),
	m_width(0),
	m_height(0)
{
}

void GridScript::start()
{
	transform = getTransform();
	m_width = transform->getSize().x;
	m_height = transform->getSize().y;

	cells.reserve(m_width*m_height);

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++) {
			string temp = "cell" + to_string(i*m_width + j);
			auto tempObject = GameObject::Instantiate(temp, "cell", gameObject, Position{ i, j }, "0");
			tempObject->addComponent<CellScript>();
			cells.push_back(tempObject);
		}
	}

	SetMine();
}

void GridScript::update()
{
	if (m_foundMine == m_mineCnt)
		m_isGameOver = true;

	if (m_isGameOver&& m_foundMine < m_mineCnt)
	{
		for (int i = 0; i < m_width*m_height; i++)
		{
			if (cells[i]->getComponent<CellScript>()->getFlag() == 9)
			{
				cells[i]->getComponent<CellScript>()->OnBomb();
			}
		}
	}

	//if (!m_isEndInit && m_isGameOver)
	//{
	//	auto endPanel = GameObject::Instantiate("Ending", "panel", nullptr,
	//		Position{ 1, 18 }, "*", Position{ 27, 4 });
	//	m_isEndInit = true;
	//}

}

void GridScript::reset()
{
	m_isGameOver = false;
	m_startFlag = false;
	m_isEndInit = false;
	m_foundMine = 0;
	for (auto cell : cells)
		cell->getComponent<CellScript>()->reset();

	SetMine();
}

void GridScript::SetMine()
{
	int data[256];
	int temp, x, y;
	int maxRandNum = m_width * m_height;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < m_width*m_height; i++)
		data[i] = i;
	for (int i = 0; i < 200; i++)
	{
		x = rand() % maxRandNum;
		y = rand() % maxRandNum;

		if (x != y)
		{
			temp = data[x];
			data[x] = data[y];
			data[y] = temp;
		}
	}

	for (int i = 0; i < m_mineCnt; i++)
	{
		cells[data[i]]->getComponent<CellScript>()->setFlag(9);
	}

	for (int i = 0; i < m_width*m_height; i++)
	{
		if (cells[i]->getComponent<CellScript>()->getFlag() != 9)
		{
			cells[i]->getComponent<CellScript>()->setFlag(MineNumCheck(i));
		}
	}
}

int GridScript::MineNumCheck(int index)
{
	int mineCnt = 0;
	int lt = index - (m_width + 1),
		t = index - m_width,
		rt = index - (m_width - 1),
		l = index - 1,
		r = index + 1,
		lb = index + (m_width - 1),
		b = index + m_width,
		rb = index + (m_width + 1);

	if (index == 0)//0
	{
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index == m_width - 1)//8
	{
		if (cells[l]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[lb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index == ((m_width*m_height) - m_width))
	{
		if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index == ((m_width*m_height) - 1))
	{
		if (cells[lt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[l]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}

	if (index < m_width)
	{
		if (cells[l]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[lb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index % m_width == 0)
	{
		if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index % m_width == (m_width - 1))
	{
		if (cells[lt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[lb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}
	if (index > ((m_width*m_height) - m_width))
	{
		if (cells[lt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[rt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[l]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
		return mineCnt;
	}

	if (cells[lt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[t]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[rt]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[l]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[r]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[lb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[b]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;
	if (cells[rb]->getComponent<CellScript>()->getFlag() == 9) mineCnt++;

	return mineCnt;
}

bool GridScript::CheckPos(int x, int y)
{
	bool flag = true;
	if (x < 0 || y < 0)
		flag = false;
	if (x >= m_width || y >= m_height)
		flag = false;
	return flag;
}

void GridScript::Bomb(int x, int y)
{
	//x -= 4; y -= 3;
	int index = x * m_width + y;
	if (cells[index]->getComponent<CellScript>()->getFlag() == 0) {
		cells[index]->getComponent<CellScript>()->OnBomb();
		if (CheckPos(x - 1, y - 1)) 
			DoubleCheck(x - 1, y - 1);
		if (CheckPos(x - 1, y + 1)) 
			DoubleCheck(x - 1, y + 1);
		if (CheckPos(x + 1, y - 1)) 
			DoubleCheck(x + 1, y - 1);
		if (CheckPos(x + 1, y + 1)) 
			DoubleCheck(x + 1, y + 1);
		if (CheckPos(x - 1, y)) 
			DoubleCheck(x - 1, y);
		if (CheckPos(x + 1, y)) 
			DoubleCheck(x + 1, y);
		if (CheckPos(x, y - 1)) 
			DoubleCheck(x, y - 1);
		if (CheckPos(x, y + 1)) 
			DoubleCheck(x, y + 1);
	}
	else if (cells[index]->getComponent<CellScript>()->getFlag() < 9)
		cells[index]->getComponent<CellScript>()->OnBomb();
}
void GridScript::DoubleCheck(int x, int y)
{
	//x -= 4; y -= 3;
	int index = x * m_width + y;
	if (cells[index]->getComponent<CellScript>()->getFlag() == 0) {
		cells[index]->getComponent<CellScript>()->OnBomb();
		if (CheckPos(x - 1, y - 1))
			TripleCheck(x - 1, y - 1);
		if (CheckPos(x - 1, y + 1))
			TripleCheck(x - 1, y + 1);
		if (CheckPos(x + 1, y - 1))
			TripleCheck(x + 1, y - 1);
		if (CheckPos(x + 1, y + 1))
			TripleCheck(x + 1, y + 1);
		if (CheckPos(x - 1, y))
			TripleCheck(x - 1, y);
		if (CheckPos(x + 1, y))
			TripleCheck(x + 1, y);
		if (CheckPos(x, y - 1))
			TripleCheck(x, y - 1);
		if (CheckPos(x, y + 1))
			TripleCheck(x, y + 1);
	}
	else if (cells[index]->getComponent<CellScript>()->getFlag() < 9)
		cells[index]->getComponent<CellScript>()->OnBomb();
}
void GridScript::TripleCheck(int x, int y)
{
	//x -= 4; y -= 3;
	int index = x * m_width + y;
	if (cells[index]->getComponent<CellScript>()->getFlag() == 0) {
		cells[index]->getComponent<CellScript>()->OnBomb();
		if (CheckPos(x - 1, y - 1))
			QuadCheck(x - 1, y - 1);
		if (CheckPos(x - 1, y + 1))
			QuadCheck(x - 1, y + 1);
		if (CheckPos(x + 1, y - 1))
			QuadCheck(x + 1, y - 1);
		if (CheckPos(x + 1, y + 1))
			QuadCheck(x + 1, y + 1);
		if (CheckPos(x - 1, y))
			QuadCheck(x - 1, y);
		if (CheckPos(x + 1, y))
			QuadCheck(x + 1, y);
		if (CheckPos(x, y - 1))
			QuadCheck(x, y - 1);
		if (CheckPos(x, y + 1))
			QuadCheck(x, y + 1);
	}
	else if (cells[index]->getComponent<CellScript>()->getFlag() < 9)
		cells[index]->getComponent<CellScript>()->OnBomb();
}
void GridScript::QuadCheck(int x, int y)
{
	//x -= 4; y -= 3;
	int index = x * m_width + y;
	if (cells[index]->getComponent<CellScript>()->getFlag() == 0) {
		cells[index]->getComponent<CellScript>()->OnBomb();
	}
	else if (cells[index]->getComponent<CellScript>()->getFlag() < 9)
		cells[index]->getComponent<CellScript>()->OnBomb();
}
