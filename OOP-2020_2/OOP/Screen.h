#pragma once
class Screen
{
private:
	//Singleton
	Screen(int width, int height);

public:
	//stctic Screen& GetInstance()
	static Screen* GetInstance()
	{
		if (!instance)			
			instance = new Screen(10,10);

		//static 지역변수 사용
		//static Screen* screen = new Screen(10,10);
		//return *screen

		return instance;
	}

	~Screen();

public:
	void Draw( int x, int y, char s);
	void Clear();
	void Render();

private:
	static Screen* instance;

	int m_width;
	int m_height;
	char* m_buffer;
};

