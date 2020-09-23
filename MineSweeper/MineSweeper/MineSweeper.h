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
	void	InitMine();
	int		GetData(int index);	

private:
	void	SetMine();
	int		MineNumCheck(int index);
	void	SetNum();
private:
	static MineSweeper* instance;

	int* m_buffer;

	int m_mineCnt;
	int m_width;
	int m_height;

};

