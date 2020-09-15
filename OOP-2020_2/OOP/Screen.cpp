#include "Screen.h"
#include <iostream>
using namespace std;

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height)
	:m_width(width+1),
	m_height(height),
	m_buffer(new char[m_width*m_height])
{
}

Screen::~Screen()
{
	delete[] m_buffer;
}

void Screen::Draw( int x, int y, char s)
{
	if (!m_buffer) return;
	m_buffer[y * m_width + x] = s;
}

void Screen::Clear()
{
	memset(m_buffer, ' ', m_width * m_height);
}

void Screen::Render()
{
	for (int i = 0; i < m_height; i++) m_buffer[m_width * i + m_height] = '\n';
	m_buffer[m_width * m_height] = '\0';

	cout << m_buffer;

}
