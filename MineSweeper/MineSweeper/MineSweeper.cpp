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

int MineSweeper::MineNumCheck(int index)
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
		if (m_buffer[r]== 9) mineCnt++;
		if (m_buffer[b] == 9) mineCnt++;
		if (m_buffer[rb] == 9) mineCnt++;
		return mineCnt;
	}
	if (index == m_width - 1)//8
	{
		if (m_buffer[l] == 9) mineCnt++;
		if (m_buffer[lb] == 9) mineCnt++;
		if (m_buffer[b] == 9) mineCnt++;
		return mineCnt;
	}
	if (index == ((m_width*m_height) - m_width))//72
	{
		if (m_buffer[t] == 9) mineCnt++;
		if (m_buffer[rt] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		return mineCnt;
	}
	if (index == ((m_width*m_height)-1))//80
	{
		if (m_buffer[lt] == 9) mineCnt++;
		if (m_buffer[t] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		return mineCnt;
	}

	if (index < m_width)//1~7
	{
		if (m_buffer[l] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		if (m_buffer[lb] == 9) mineCnt++;
		if (m_buffer[b] == 9) mineCnt++;
		if (m_buffer[rb] == 9) mineCnt++;
		return mineCnt;
	}
	if (index % m_width == 0)//9,18,27...
	{
		if (m_buffer[t] == 9) mineCnt++;
		if (m_buffer[rt] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		if (m_buffer[b] == 9) mineCnt++;
		if (m_buffer[rb] == 9) mineCnt++;
		return mineCnt;
	}
	if (index % m_width == (m_width-1))//17,26,35...
	{
		if (m_buffer[lt] == 9) mineCnt++;
		if (m_buffer[t] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		if (m_buffer[lb] == 9) mineCnt++;
		if (m_buffer[b] == 9) mineCnt++;
		return mineCnt;
	}
	if (index > ((m_width*m_height) - m_width))//73,74,75...
	{
		if (m_buffer[lt] == 9) mineCnt++;
		if (m_buffer[t] == 9) mineCnt++;
		if (m_buffer[rt] == 9) mineCnt++;
		if (m_buffer[l] == 9) mineCnt++;
		if (m_buffer[r] == 9) mineCnt++;
		return mineCnt;
	}

	if (m_buffer[lt] == 9) mineCnt++;
	if (m_buffer[t] == 9) mineCnt++;
	if (m_buffer[rt] == 9) mineCnt++;
	if (m_buffer[l] == 9) mineCnt++;
	if (m_buffer[r] == 9) mineCnt++;
	if (m_buffer[lb] == 9) mineCnt++;
	if (m_buffer[b] == 9) mineCnt++;
	if (m_buffer[rb] == 9) mineCnt++;

	return mineCnt;
}

void MineSweeper::SetNum()
{
	for (int i = 0; i < m_width*m_height; i++)
	{
		if (m_buffer[i] != 9)
		{
			m_buffer[i] = MineNumCheck(i);
		}
	}
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
