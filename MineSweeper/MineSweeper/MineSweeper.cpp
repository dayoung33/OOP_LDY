#include "MineSweeper.h"
#include <iostream>
#include <time.h>

MineSweeper* MineSweeper::instance = nullptr;


MineSweeper::MineSweeper(int width, int height)
	:m_width(width),
	m_height(height),
	m_mineCnt(10),
	m_buffer(new int[m_width*m_height])
{
	memset(m_buffer, 0, m_width * m_height);
}

MineSweeper::~MineSweeper()
{
	delete[] m_buffer;
}

void MineSweeper::InitMine()
{
	for (int i = 0; i < m_width*m_height; i++)
		m_buffer[i] = 0;

	SetMine();
	SetNum();
}

int MineSweeper::GetData(int index)
{
	return m_buffer[index];
}

int MineSweeper::MineNumCheck(int x_pos, int y_pos)
{
	int mineCnt = 0;
	if (PosCheck(x_pos - 1, y_pos - 1))mineCnt++;
	if (PosCheck(x_pos - 1, y_pos))mineCnt++;
	if (PosCheck(x_pos - 1, y_pos + 1))mineCnt++;
	if (PosCheck(x_pos, y_pos + 1))mineCnt++;
	if (PosCheck(x_pos, y_pos - 1))mineCnt++;
	if (PosCheck(x_pos + 1, y_pos - 1))mineCnt++;
	if (PosCheck(x_pos + 1, y_pos))mineCnt++;
	if (PosCheck(x_pos + 1, y_pos + 1))mineCnt++;

	return mineCnt;
}

void MineSweeper::SetNum()
{
	for (int i = 0; i < m_width*m_height; i++)
	{
		if (m_buffer[i] == 0)
		{
			m_buffer[i] = MineNumCheck(i % m_width, i / m_height);
		}
	}
}

bool MineSweeper::PosCheck(int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos >= m_width || y_pos < 0 || y_pos <= m_height)
		return false;

	return (m_buffer[y_pos * m_width + x_pos] == 9);
}

void MineSweeper::SetMine()
{
	int data[100];
	int temp, x, y;
	int maxRandNum = m_width * m_height;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < m_width*m_height; i++) 
		data[i] = i;
	for (int i = 0; i < 100; i++)
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
		m_buffer[data[i]] = 9;
		printf("%d  ", data[i]);
	}
}

void MineSweeper::GameLoop(int x_pos, int y_pos)
{

}
