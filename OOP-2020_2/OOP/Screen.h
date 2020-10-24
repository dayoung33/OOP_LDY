#pragma once

#include "Utils.h"
#include <cstdlib> 
#include <iostream>
using namespace std;

class Screen
{
private:
	//Singleton
	Screen(int width, int height);

public:
	static Screen* getInstance() {
		if (instance == nullptr) {
			instance = new Screen{ 80, 30 };
		}
		return instance;
	}

	~Screen();

public:
	int getWidth() const { return m_width; }
	int getScreenWidth() const { return m_width + 1; }
	int getHeight() const { return m_height; }
	int getSize() const { return getScreenWidth()*m_height; }

	void clear();

	void draw( int x, int y, const char shape);
	void draw(int x, int y, const char * shape, int len);
	void draw(const Position& pos, char shape); 
	void draw(const Position& pos, const char* shape);
	void draw(const Position& pos, const char* shape, int len);
	void drawLineHorizontal(const Position& pos, int width);
	void drawLineVertical(const Position& pos, int height);
	void drawRectangle(const Position& topLeft, const Position& sz);
	void drawShape(const Position& pos, const Position& sz, const char* shape);

	void render();

private:
	static Screen* instance;

	int m_width;
	int m_height;
	char* m_buffer;
};

