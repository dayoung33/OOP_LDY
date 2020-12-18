#include "GridScript.h"
#include "GameObject.h"
#include "CellScript.h"
#include <time.h>

GridScript::GridScript(GameObject * gameObject)
	:Component(gameObject), m_isGameOver(false),m_mineCnt(10), m_foundMine(0), m_width(0), m_height(0)
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
			auto tempObject = GameObject::Instantiate(temp, "cell", gameObject, Position{ i+4, j+3 }, "");
			tempObject->addComponent<CellScript>();
			cells.push_back(tempObject);
		}
	}

	SetMine();
}

void GridScript::update()
{
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

