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
			instance = new Screen(80,20);

		return instance;
	}

	~Screen();

public:
	void draw( int x, int y, char s);
	void draw(int x, int y, const char* shape);
	void clear();
	void render();

private:
	static Screen* instance;

	int m_width;
	int m_height;
	char* m_buffer;
};

