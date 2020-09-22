#pragma once
class MineSweeper
{
private:
	//Singleton
	MineSweeper(int width, int height);

public:
	static MineSweeper* GetInstance(int width, int height)
	{
		if (!instance)
			instance = new MineSweeper(width, height);

		return instance;
	}

	~MineSweeper();

public:
	int GetData(int index);
	void SetMine();

private:
	static MineSweeper* instance;

	int* m_buffer;

	int m_mineCnt;
	int m_width;
	int m_height;

};

