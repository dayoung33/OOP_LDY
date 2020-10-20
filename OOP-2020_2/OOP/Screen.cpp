#include "Screen.h"

Screen* Screen::instance = nullptr;

Screen::Screen(int width, int height)
	:m_width(width),
	m_height(height), m_buffer{ new char[getSize()] }
{
	Borland::initialize();
	m_buffer[getSize() - 1] = '\0';
}

Screen::~Screen()
{
	delete[] m_buffer;
}

void Screen::draw( int x, int y, const char shape)
{
	if (!m_buffer) return;
	m_buffer[y * m_width + x] = shape;
}

void Screen::draw(int x, int y, const char * shape,int len)
{
	if (shape == nullptr || len == 0 || len > strlen(shape)) return;
	strncpy(&m_buffer[y* getScreenWidth() + x], shape, len);
	strncpy(&m_buffer[y* m_width + x], shape, strlen(shape));
}

void Screen::draw(const Position & pos, char shape)
{
	 draw(pos.x, pos.y, shape); 
}

void Screen::draw(const Position & pos, const char * shape)
{
	draw(pos.x, pos.y, shape, strlen(shape));
}

void Screen::draw(const Position & pos, const char * shape, int len)
{
	draw(pos.x, pos.y, shape, len);
}

void Screen::drawLineHorizontal(const Position & pos, int width)
{
	if (pos.x < 0 || pos.y < 0 || pos.x + width > getWidth() || pos.y > getHeight()) return;
	for (int i = pos.x; i <= min(this->m_width, pos.x + width); i++) draw(i, pos.y, 196);
}

void Screen::drawLineVertical(const Position & pos, int height)
{
	if (pos.x < 0 || pos.y < 0 || pos.x > getWidth() || pos.y + height > getHeight()) return;
	for (int i = pos.y; i <= min(this->m_height, pos.y + height); i++) draw(pos.x, i, 179);
}

void Screen::drawRectangle(const Position & topLeft, const Position & sz)
{
	drawLineHorizontal(topLeft, sz.x);
	drawLineHorizontal(topLeft + Position{ 0, sz.y }, sz.x);
	drawLineVertical(topLeft, sz.y);
	drawLineVertical(topLeft + Position{ sz.x, 0 }, sz.y);
	draw(topLeft, 218); draw(topLeft + Position{ sz.x, 0 }, 191);
	draw(topLeft + Position{ 0, sz.y }, 192); draw(topLeft + sz, 217);
}

void Screen::drawShape(const Position & pos, const Position & sz, const char * shape)
{
	if (shape == nullptr) return;
	for (int i = 0; i < sz.y; i++) draw(pos.x, pos.y + i, &shape[i*sz.x], sz.x);
}

void Screen::clear()
{
	memset(m_buffer, ' ', m_width * m_height);
}

void Screen::render()
{
	for (int y = 0; y < m_height - 1; y++)
		draw(m_width, y, '\n');
	draw(m_width - 1, m_height, '\0');

	Borland::gotoxy(0, 0);	
	cout << m_buffer;
}
