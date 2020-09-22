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

int MineSweeper::GetData(int index)
{
	return m_buffer[index];
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
		m_buffer[data[i]] = i+1;
		printf("%d  ", data[i]);
	}
}
