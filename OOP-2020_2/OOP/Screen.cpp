#include "Screen.h"
#include "Utils.h"
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

void Screen::draw( int x, int y, char s)
{
	if (!m_buffer) return;
	m_buffer[y * m_width + x] = s;
}

void Screen::draw(int x, int y, const char * shape)
{
	strncpy(&m_buffer[y* m_width + x], shape, strlen(shape));
}

void Screen::clear()
{
	memset(m_buffer, ' ', m_width * m_height);
}

void Screen::render()
{

	for (int i = 0; i < m_height; i++) m_buffer[m_width * i + m_height] = '\n';
	m_buffer[m_width * m_height] = '\0';

	Borland::gotoxy(0, 0);	
	cout << m_buffer;

}
