#include "Screen.h"
#include <iostream>
using namespace std;

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height)
	:m_width(width),
	m_height(height),
	m_checkCnt(0)
{
	m_buffer = new char[m_width*m_height];
}

Screen::~Screen()
{
	delete[] m_buffer;
}

void Screen::Draw( int x, int y, char s)
{
	if (!m_buffer) return;
	if (s > 57) return;
	m_buffer[y * m_width + x] = s;
}

void Screen::IndexDraw(int index, char s)
{
	if (!m_buffer) return;
	m_buffer[index] = s;
}

void Screen::Clear()
{
	memset(m_buffer, '0', m_width * m_height);
	//for (int i = 0; i < m_width*m_height; i++)
	//	m_buffer[i] = '0';
}

void Screen::Render()
{
	//for (int i = 0; i < m_height; i++) m_buffer[m_width * i + m_height] = '\n';
	//m_buffer[m_width * m_height] = '\0';

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			cout << m_buffer[i*m_width+j];
		}
		cout << endl;
	}
	
}

char Screen::GetChar(int x, int y)
{
	return m_buffer[y * m_width + x];
}

int Screen::GetCheckNum()
{
	m_checkCnt = 0;
	for (int i = 0; i < m_width*m_height; i++)
	{
		if (m_buffer[i] == '*')
			m_checkCnt++;
	}
	return m_checkCnt;

}
