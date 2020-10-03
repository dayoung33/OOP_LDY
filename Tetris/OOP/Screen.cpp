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

void Screen::SetTable()
{
	const string& shape = "¢Ë";
	const string& shape2 = "-";


	for (int j = 0; j < m_height-1; j++) {			
		draw(0, j, shape.c_str());
	}
	for (int j = 0; j < m_height-1; j++) {
		draw(m_width-2, j, shape.c_str());
	}
	for (int j = 2; j < m_width-3; j++) {
		if (j % 2 == 0)
			draw(j, 4, shape2.c_str());
	}
	for (int j = 0; j < m_width-1; j++) {
		if (j % 2 == 0)
			draw(j, m_height-1, shape.c_str());
	}

}
