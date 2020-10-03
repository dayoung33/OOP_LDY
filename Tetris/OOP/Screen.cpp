#include "Screen.h"
#include "Utils.h"
#include <iostream>
using namespace std;

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height)
	:m_width(width),
	m_height(height)	
{
	m_buffer = new char[getSize()];
}

Screen::~Screen()
{
	delete[] m_buffer;
}

void Screen::draw( int x, int y, char s)
{
	if (!m_buffer) return;
	m_buffer[y * getScreenWidth() + x] = s;
}

void Screen::draw(int x, int y, const char * shape)
{
	strncpy(&m_buffer[y* getScreenWidth() + x], shape, strlen(shape));
}

void Screen::clear()
{
	memset(m_buffer, ' ', getSize());
}

void Screen::render()
{
	for (int i = 0; i < m_height-1; i++)
		m_buffer[getScreenWidth() * i + m_width] = '\n';
	m_buffer[getSize()-1] = '\0';

	Borland::gotoxy(0, 0);	
	cout << m_buffer;
}

