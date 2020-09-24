#include "MineSweeper.h"
#include "Screen.h"
#include <iostream>
#include <time.h>

MineSweeper* MineSweeper::instance = nullptr;

MineSweeper::MineSweeper(int width, int height)
	:m_width(width),
	m_height(height),
	m_mineCnt(10),
	m_foundMine(0),
	gameover(false),
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

void MineSweeper::SetScreen(Screen* _screen)
{
	screen = _screen;
}

int MineSweeper::GetData(int index)
{
	return m_buffer[index];
}

int MineSweeper::GetFindMineNum()
{
	m_foundMine = 0;
	for (int i = 0; i < m_width*m_height; i++)
	{
		if (m_buffer[i] == -1)
			m_foundMine++;
	}
	return m_foundMine;
}

bool MineSweeper::GetOver()
{
	return gameover;
}

bool MineSweeper::GetClear()
{
	return m_mineCnt == GetFindMineNum();
}

void MineSweeper::CheckMine(int xpos, int ypos, bool check)
{
	if (check) 
	{
		if (m_buffer[xpos + (ypos*m_width)] == 9)
		{
			m_buffer[xpos + (ypos*m_width)] = -1;
		}
	}
	else
	{
		if (m_buffer[xpos + (ypos*m_width)] == -1)
		{
			m_buffer[xpos + (ypos*m_width)] = 9;
		}
	}
}

void MineSweeper::GameLoop(int xpos, int ypos)
{
	int index = xpos + (ypos * m_width);

	if (m_buffer[index] == 9)
	{
		for (int i = 0; i < m_width*m_height; i++)
		{
			if (m_buffer[i] == 9)
				screen->IndexDraw(i, '@');
		}
		gameover = true;
		return;
	}
	if (m_buffer[index] > 0)
	{
		screen->IndexDraw(index, m_buffer[index] + 48);
		return;
	}
	if (m_buffer[index] == 0)
	{
		screen->Draw(xpos, ypos, ' ');
		if (Bomb(xpos - 1, ypos - 1))	{
			DoubleCheck(xpos - 1, ypos - 1);
		}	// ¢Ø
		 if (Bomb(xpos - 1, ypos + 1))	{
			 DoubleCheck(xpos - 1, ypos + 1);
		 }	// ¢× 
		 if (Bomb(xpos + 1, ypos - 1))	{
			 DoubleCheck(xpos + 1, ypos - 1);
		 }	// ¢Ö
		 if (Bomb(xpos + 1, ypos + 1))	{ 
			 DoubleCheck(xpos + 1, ypos + 1);
		 }	// ¢Ù
		 if (Bomb(xpos - 1, ypos))		{	 
			 DoubleCheck(xpos - 1, ypos);
		 }// ¡ç
		 if (Bomb(xpos + 1, ypos))		{ 
			 DoubleCheck(xpos + 1, ypos);
		 }// ¡æ
		 if (Bomb(xpos, ypos - 1))		{ 
			 DoubleCheck(xpos , ypos - 1);
		 }// ¡è
		 if (Bomb(xpos, ypos + 1))		{
			 DoubleCheck(xpos, ypos + 1);
		 }// ¡é

		return;
	}
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


void MineSweeper::DoubleCheck(int x, int y)
{
	if (m_buffer[x + m_width * y] == 0){
		screen->Draw(x, y, ' ');
		if (Bomb(x - 1, y - 1)) {
			TripleCheck(x - 1, y - 1);
		}	// ¢Ø
		if (Bomb(x - 1, y + 1)) {
			TripleCheck(x - 1, y + 1);
		}	// ¢× 
		if (Bomb(x + 1, y - 1)) {
			TripleCheck(x + 1, y - 1);
		}	// ¢Ö
		if (Bomb(x + 1, y + 1)) {
			TripleCheck(x + 1, y + 1);
		}	// ¢Ù
		if (Bomb(x - 1, y)) {
			TripleCheck(x - 1, y);
		}// ¡ç
		if (Bomb(x + 1, y)) {
			TripleCheck(x + 1, y);
		}// ¡æ
		if (Bomb(x, y - 1)) {
			TripleCheck(x, y - 1);
		}// ¡è
		if (Bomb(x, y + 1)) {
			TripleCheck(x, y + 1);
		}// ¡é
	}
	else if (m_buffer[x+ m_width * y] < 9)
		screen->Draw(x, y, m_buffer[x + m_width * y] + 48);
}
void MineSweeper::TripleCheck(int x, int y)
{
	if (m_buffer[x + m_width * y] == 0) {
		screen->Draw(x, y, ' ');
		if (Bomb(x - 1, y - 1)) {
			QuadCheck(x - 1, y - 1);
		}	// ¢Ø
		if (Bomb(x - 1, y + 1)) {
			QuadCheck(x - 1, y + 1);
		}	// ¢× 
		if (Bomb(x + 1, y - 1)) {
			QuadCheck(x + 1, y - 1);
		}	// ¢Ö
		if (Bomb(x + 1, y + 1)) {
			QuadCheck(x + 1, y + 1);
		}	// ¢Ù
		if (Bomb(x - 1, y)) {
			QuadCheck(x - 1, y);
		}// ¡ç
		if (Bomb(x + 1, y)) {
			QuadCheck(x + 1, y);
		}// ¡æ
		if (Bomb(x, y - 1)) {
			QuadCheck(x, y - 1);
		}// ¡è
		if (Bomb(x, y + 1)) {
			QuadCheck(x, y + 1);
		}// ¡é
	}
	else if (m_buffer[x + m_width * y] < 9)
		screen->Draw(x, y, m_buffer[x + m_width * y] + 48);
}
void MineSweeper::QuadCheck(int x, int y)
{
	if (m_buffer[x + m_width * y] == 0) {
		screen->Draw(x, y, ' ');
	}
	else if (m_buffer[x + m_width * y] < 9)
		screen->Draw(x, y, m_buffer[x + m_width * y] + 48);
}

bool MineSweeper::Bomb(int x, int y)
{
	bool flag = true;
	if (x < 0 || y < 0) 
		flag = false; 
	if (x >= m_width || y >= m_height) 
		flag = false; 
	return flag;
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
	}
	printf("Áö·Ú °³¼ö :%d  ", m_mineCnt);
}
