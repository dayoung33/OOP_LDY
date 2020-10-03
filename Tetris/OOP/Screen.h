#pragma once
class Screen
{
private:
	//Singleton
	Screen(int width, int height);

public:
	static Screen* getInstance()
	{
		if (!instance)			
			instance = new Screen(30,30);

		return instance;
	}

	~Screen();

public:
	void draw( int x, int y, char s);
	void draw(int x, int y, const char* shape);
	void clear();
	void render();
	void SetTable();

private:
	//int getWidth() const { return m_width; }
	int getScreenWidth() const { return m_width + 1; }
	//int getHeight() const { return m_height; }
	int getSize() const { return getScreenWidth()*m_height; }

private:
	static Screen* instance;

	int m_width;
	int m_height;
	char* m_buffer;
};

