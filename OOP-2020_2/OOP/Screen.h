#pragma once
class Screen
{
public:
	Screen(int width, int height);
	~Screen();

public:
	void Draw( int x, int y, char s);
	void Clear();
	void Render();

private:
	int m_width;
	int m_height;
	char* m_buffer;
};

